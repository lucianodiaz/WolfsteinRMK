#include <vector>
#include "Camera2d.h"
#include "Global.h"
#include "Map.h"
#include "World.h"
#include "Enemy.h"
#include "AnimationManager.h"
#include <iostream>
Camera2d::Camera2d(World& _world, sf::Vector2f& _position, sf::Vector2f& direction, sf::Vector2f size, sf::Vector2f& plane) :
    _world(_world), _position(_position), _direction(direction), size(size), _plane(plane)
{
    _lines = sf::VertexArray(sf::Lines, 18*_world.getWidth());
    

    _currentState = &Configuration::textures.get(Configuration::Textures::Walls);

    _direction = rotateVec(direction, 5.0f);
    _plane = rotateVec(_plane,5.0f);

    
    _spriteOrder = std::vector(_world.getMap().getSprites().size(), 0);
    _spriteDistance = std::vector(_world.getMap().getSprites().size(), 0.0);

    _ZBuffer = std::vector(_world.getWidth(), 0.0);

}


void Camera2d::Raycasting(float rotation)
{
   
    _direction = rotateVec(_direction, rotation);
    _plane = rotateVec(_plane, rotation);

    RaycastinWalls();
    //Start Raycasting Sprite
    RaycastingSprite();


}

void Camera2d::RaycastinWalls()
{
    _lines.resize(0);

    int screenWidth = _world.getWidth();
    int screenHeight = _world.getHeight();
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

        float perpWallDist = 0.0f; // wall distance, projected on camera direction
        int wallHeight; // height of wall to draw on the screen at each distance
        int ceilingPixel = 0; // position of ceiling pixel on the screen
        int groundPixel = screenHeight; // position of ground pixel on the screen

        // colors for floor tiles
        sf::Color color1 = sf::Color::White;

        // current floor color
        sf::Color color = color1;

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

            _lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(500.0f, 500.0f)));
            groundPixel = int(wallHeight * cameraHeight + screenHeight * 0.5f);
            _lines.append(sf::Vertex(sf::Vector2f((float)x, (float)groundPixel), color, sf::Vector2f(500.0f, 500.0f)));

            // add ceiling

            sf::Color color_c = color;
            color_c.r /= 2;
            color_c.g /= 2;
            color_c.b /= 2;

            _lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(500.0f, 500.0f)));
            ceilingPixel = int(-wallHeight * (1.0f - cameraHeight) + screenHeight * 0.5f);
            _lines.append(sf::Vertex(sf::Vector2f((float)x, (float)ceilingPixel), color_c, sf::Vector2f(500.0f, 500.0f)));

            // change color and find tile type

            color = color1;

            tile = _world.getMap().getTile(mapPos.x, mapPos.y);


        }

        // calculate lowest and highest pixel to fill in current line
        int drawStart = ceilingPixel;
        int drawEnd = groundPixel;

        // get position of the wall texture in the full texture
        int wallTextureNum = (int)_world.getMap().wallTypes.find(tile)->second;
        //the eleven it's a magic number i don't know why textures don't drawed well so a add this number offset
        //to fix that and for now works well
        sf::Vector2i texture_coords(
            wallTextureNum * texture_wall_size % texture_size - 1,
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
        _lines.append(sf::Vertex(
            sf::Vector2f((float)x, (float)drawStart),
            color,
            sf::Vector2f((float)texture_coords.x, (float)texture_coords.y + 1)
        ));
        _lines.append(sf::Vertex(
            sf::Vector2f((float)x, (float)drawEnd),
            color,
            sf::Vector2f((float)texture_coords.x, (float)(texture_coords.y + texture_wall_size - 1))
        ));

        _ZBuffer.at(x) = perpWallDist;
    }


}

void Camera2d::RaycastingSprite()
{
    sf::VertexArray spriteLines(sf::Lines, _world.getWidth());
    spriteLines.resize(0);
    spriteLines.clear();
    for (auto s : _world.getMap().getSprites())
    {
        if (s->isAlive())
        {
            s->_spriteLines = spriteLines;
        }
       
    }
    unsigned int numberOfSprites = _world.getMap().getSprites().size();

    for (int i = 0; i < numberOfSprites; i++) {
        auto sprite = _world.getMap().getSprites().at(i);
        _spriteOrder.at(i) = i;
        _spriteDistance.at(i) = ((_position.x- sprite->getGridPosition().x) * (_position.x - sprite->getGridPosition().x) +
            (_position.y- sprite->getGridPosition().y) * (_position.y - sprite->getGridPosition().y));

    }

    sortSprites(&_spriteOrder, &_spriteDistance, numberOfSprites);

    for (int j = 0; j < numberOfSprites; j++)
    {
        //Limit draw distance 
        if (_spriteDistance[j] < 500 )
        {
            auto sprite = _world.getMap().getSprites().at(_spriteOrder[j]);

            sprite->_spriteLines.clear();

            double spriteX = sprite->getGridPosition().x - _position.x;
            double spriteY = sprite->getGridPosition().y - _position.y;

            double invDet = 1.0 / (_plane.x * _direction.y - _direction.x * _plane.y);

            double transformX = invDet * (_direction.y * spriteX - _direction.x * spriteY);
            double transformY = invDet * (-_plane.y * spriteX + _plane.x * spriteY);

            int spriteScreenX = int(((float)_world.getWidth() / 2) * (1 + transformX / transformY));

            //stuff for scaling and moving sprites to the floor
#define vMove 128
#define SpriteScale 1
            int vMoveScreen = int(vMove / transformY);

            //stuff for scaling sprite in Y axis
            int overflowPixels = 0;
            int pixelAdjustment = 0;

            int spriteHeight = abs(int(_world.getHeight() / (transformY))) / SpriteScale;

            int drawStartY = -spriteHeight / 2 + _world.getHeight() / 2 + vMoveScreen;

            if (drawStartY < 0) drawStartY = 0;

            int drawEndY = spriteHeight / 2 + _world.getHeight() / 2 + vMoveScreen;

            if (drawEndY > _world.getHeight())
            {
                overflowPixels = drawEndY - _world.getHeight();
                //pixelAdjustment = texWidth / _world.getHeight();
                drawEndY = _world.getHeight() + 100;
            }

            //calculating X axis variable

            int spriteWidth = abs(int(_world.getHeight() / (transformY))) / SpriteScale;

            int drawStartX = -spriteWidth / 2 + spriteScreenX;
            if (drawStartX < 0)
            {
                drawStartX = 0;
            }
            int drawEndX = spriteWidth / 2 + spriteScreenX;
            if (drawEndX >= _world.getWidth())
            {
                drawEndX = _world.getWidth() - 1;
            }

            for (int stripe = drawStartX; stripe < drawEndX; stripe++)
            {
                int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;

                if (transformY > 0 && stripe > 0 && stripe < _world.getWidth() && transformY < _ZBuffer[stripe])
                {
                    if (dynamic_cast<Enemy*>(sprite))
                    {
                        auto s = dynamic_cast<Enemy*>(sprite);

                        spriteLines.append(sf::Vertex(sf::Vector2f((float)stripe, (float)drawStartY),
                            sf::Vector2f((float)texX + s->_animationManager->uvRect.left, (float)(s->_animationManager->uvRect.top - s->_animationManager->uvRect.height))));

                        spriteLines.append(sf::Vertex(sf::Vector2f((float)stripe, (float)drawEndY),
                            sf::Vector2f((float)texX + s->_animationManager->uvRect.left, (float)(s->_animationManager->uvRect.top - 1 - pixelAdjustment))));
                    }
                    else
                    {
                        spriteLines.append(sf::Vertex(sf::Vector2f((float)stripe, (float)drawStartY),
                            sf::Vector2f((float)texX, (float)(0))));

                        spriteLines.append(sf::Vertex(sf::Vector2f((float)stripe, (float)drawEndY),
                            sf::Vector2f((float)texX, (float)(texWidth - 1 - pixelAdjustment))));
                    }


                    sprite->_spriteLines = spriteLines;
                }
            }
        }
        
    }

    spriteLines.clear();
}

void Camera2d::sortSprites(std::vector<int>* order, std::vector<double>* dist, int amount)
{
    std::vector<std::pair<double, int>> sprites(amount);
    for (int i = 0; i < amount; i++)
    {
        sprites[i].first = dist->at(i);
        sprites[i].second = order->at(i);
    }
    std::sort(sprites.begin(), sprites.end());

    for (int i = 0; i < amount; i++)
    {
        dist->at(i) = sprites[amount - i - 1].first;
        order->at(i) = sprites[amount - i - 1].second;
    }
}

sf::Vector2f Camera2d::rotateVec(sf::Vector2f vec, float value) const
{
    return sf::Vector2f(
        vec.x * std::cos(value) - vec.y * std::sin(value),
        vec.x * std::sin(value) + vec.y * std::cos(value)
    );
}

void Camera2d::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(_lines, _currentState);
   
    for (auto sprite : _world.getMap().getSprites())
    {
        if (sprite->isAlive())
            sprite->draw(target, states);
    }
    
}

void Camera2d::restart()
{
    _ZBuffer.clear();
    _spriteOrder.clear();
    _spriteDistance.clear();
}
