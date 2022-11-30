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

    _direction = rotateVec(_direction,2.0f);
    _plane = rotateVec(_plane, 2.0f);

    _position = Configuration::getInitialPos();

	_camera = std::make_unique<Camera2d>(_world, _position, _direction, sf::Vector2f(_size_f, _size_f),_plane);
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
        /*sf::Vector2f lastPosition = (_position);*/
        
		sf::Vector2f moveVec = _direction * (_moveSpeed * _moveForward * seconds);

        if (Collision::canMove(sf::Vector2f(_position.x + moveVec.x, _position.y), size,_world.getMap()))
        {
            _position.x += moveVec.x;
        }
        if (Collision::canMove(sf::Vector2f(_position.x, _position.y + moveVec.y), size, _world.getMap()))
        {
            _position.y += moveVec.y;
        }
	}

	if (_rotateDirection != 0.0f)
	{
		float rotation = _rotationSpeed * _rotateDirection * seconds;
		_direction = rotateVec(_direction, rotation);
		_plane = rotateVec(_plane, rotation);
	}

    raycasting();
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
	_camera->draw(target,states);
	Entity::draw(target, states);
	
}

void Player::raycasting()
{
	_camera->Raycasting();
}

sf::Vector2f Player::rotateVec(sf::Vector2f vec, float value) const
{
	return sf::Vector2f(
        vec.x * std::cos(value) - vec.y * std::sin(value),
        vec.x * std::sin(value) + vec.y * std::cos(value)
	);
}
