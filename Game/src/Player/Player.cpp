#include "player/Player.h"
#include "Configuration.h"
#include "Collision.h"
#include <iostream>
#include <cmath>
#include "Global.h"
#include "Map.h"

Player::Player(World& world) : Entity(Configuration::Textures::PlayerTexture,world),
							   ActionTarget(Configuration::playerInputs)
{
	lines = sf::VertexArray(sf::Lines, 18 * _world.getX());

	bind(Configuration::PlayerInputs::Left, [this](const sf::Event&) {
		_rotateDirection = -1;
		});

	bind(Configuration::PlayerInputs::Right, [this](const sf::Event&) {
		_rotateDirection = 1;
		});

	bind(Configuration::PlayerInputs::Up, [this](const sf::Event&) {
		_moveForward = 1;
	});
	bind(Configuration::PlayerInputs::Down, [this](const sf::Event&) {
		_moveForward = -1;
		});

	_state = &Configuration::textures.get(Configuration::Textures::Walls);
	
}

bool Player::isCollide(const Entity& other) const
{
	return false;
}

void Player::update(sf::Time deltaTime)
{

	float seconds = deltaTime.asSeconds();

	if (_moveForward != 0.0f)
	{
		sf::Vector2f moveVec = _direction * (_moveSpeed * _moveForward * seconds);

		if (Collision::mapCollision(_position.x +moveVec.x, _position.y, _world.getMap()))
		{
			_position.y += moveVec.y;
		}
		if (Collision::mapCollision(_position.x, _position.y + moveVec.y, _world.getMap()))
		{
			_position.x += moveVec.x;
		}
	}

	if (_rotateDirection != 0.0f)
	{
		float rotation = _rotationSpeed * _rotateDirection * seconds;
		_direction = rotateVec(_direction, rotation);
		_plane = rotateVec(_plane, rotation);
	}

	lines.resize(0);

    int screenWidth = _world.getX();
    int screenHeight = _world.getY();
    // loop through vertical screen lines, draw a line of wall for each
    for (int x = 0; x < screenWidth; ++x) {

        // ray to emit
        float cameraX = 2 * x / (float)screenWidth - 1.0f; // x in camera space (between -1 and +1)
        sf::Vector2f rayPos = _position;
        sf::Vector2f rayDir = _direction + _plane * cameraX;

        // NOTE: with floats, division by zero gives you the "infinity" value. This code depends on this.

        // calculate distance traversed between each grid line for x and y based on direction
        sf::Vector2f deltaDist(
            sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
            sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y))
        );

        sf::Vector2i mapPos(rayPos); // which box of the map we're in

        sf::Vector2i step; // what direction to step in (+1 or -1 for each dimension)
        sf::Vector2f sideDist; // distance from current position to next gridline, for x and y separately

        // calculate step and initial sideDist
        if (rayDir.x < 0.0f) {
            step.x = -1;
            sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
        }
        else {
            step.x = 1;
            sideDist.x = (mapPos.x + 1.0f - rayPos.x) * deltaDist.x;
        }
        if (rayDir.y < 0.0f) {
            step.y = -1;
            sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
        }
        else {
            step.y = 1;
            sideDist.y = (mapPos.y + 1.0f - rayPos.y) * deltaDist.y;
        }

        char tile = Cell::Empty; // tile type that got hit
        bool horizontal; // did we hit a horizontal side? Otherwise it's vertical

        float perpWallDist = 1.0f; // wall distance, projected on camera direction
        int wallHeight; // height of wall to draw on the screen at each distance
        int ceilingPixel = 0; // position of ceiling pixel on the screen
        int groundPixel = screenHeight; // position of ground pixel on the screen

        // colors for floor tiles
        sf::Color color1 = sf::Color(128,128,128);
        sf::Color color2 = sf::Color(128, 128, 128);

        // current floor color
        sf::Color color = ((mapPos.x % 2 == 0 && mapPos.y % 2 == 0) ||
            (mapPos.x % 2 == 1 && mapPos.y % 2 == 1)) ? color1 : color2;

        // cast the ray until we hit a wall, meanwhile draw floors
        while (tile == Cell::Empty) {
            if (sideDist.x < sideDist.y) {
                sideDist.x += deltaDist.x;
                mapPos.x += step.x;
                horizontal = true;
                perpWallDist = (mapPos.x - rayPos.x + (1 - step.x) / 2) / rayDir.x;
            }
            else {
                sideDist.y += deltaDist.y;
                mapPos.y += step.y;
                horizontal = false;
                perpWallDist = (mapPos.y - rayPos.y + (1 - step.y) / 2) / rayDir.y;
            }

            wallHeight = screenHeight / perpWallDist;

            // add floor

            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(385.0f, 129.0f)));
            groundPixel = int(wallHeight * cameraHeight + screenHeight * 0.5f);
            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(385.0f, 129.0f)));

            // add ceiling

            sf::Color color_c = color;
            color_c.r /= 2;
            color_c.g /= 2;
            color_c.b /= 2;

            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(385.0f, 129.0f)));
            ceilingPixel = int(-wallHeight * (1.0f - cameraHeight) + screenHeight * 0.5f);
            lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(385.0f, 129.0f)));

            // change color and find tile type

            color = (color == color1) ? color2 : color1;

            tile = _world.getMap().getTile(mapPos.x, mapPos.y);
        }

        // calculate lowest and highest pixel to fill in current line
        int drawStart = ceilingPixel;
        int drawEnd = groundPixel;

        // get position of the wall texture in the full texture
        int wallTextureNum = 1;//(int)wallTypes.find(tile)->second;
        sf::Vector2i texture_coords(
            wallTextureNum * texture_wall_size % texture_size,
            wallTextureNum * texture_wall_size / texture_size * texture_wall_size
        );

        // calculate where the wall was hit
        float wall_x;
        if (horizontal) {
            wall_x = rayPos.y + perpWallDist * rayDir.y;
        }
        else {
            wall_x = rayPos.x + perpWallDist * rayDir.x;
        }
        wall_x -= floor(wall_x);

        // get x coordinate on the wall texture
        int tex_x = int(wall_x * float(texture_wall_size));

        // flip texture if we see it on the other side of us, this prevents a mirrored effect for the texture
        if ((horizontal && rayDir.x <= 0) || (!horizontal && rayDir.y >= 0)) {
            tex_x = texture_wall_size - tex_x - 1;
        }

        texture_coords.x += tex_x;

        // illusion of shadows by making horizontal walls darker
        color = sf::Color::White;
        if (horizontal) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        // add line to vertex buffer
        lines.append(sf::Vertex(
            sf::Vector2f((float)x, (float)drawStart),
            color,
            sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1)
        ));
        lines.append(sf::Vertex(
            sf::Vector2f((float)x, (float)drawEnd),
            color,
            sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + texture_wall_size - 1))
        ));
    }
}

void Player::processEvents()
{
	_rotateDirection = 0.0f;
	_moveForward = 0.0f;
	ActionTarget::processEvents();
}

void Player::onDestroy()
{
	Entity::onDestroy();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(lines, _state);
	Entity::draw(target, states);
	
}

sf::Vector2f Player::rotateVec(sf::Vector2f vec, float value) const
{
	return sf::Vector2f(
        vec.x * std::cos(value) - vec.y * std::sin(value),
        vec.x * std::sin(value) + vec.y * std::cos(value)
	);
}
