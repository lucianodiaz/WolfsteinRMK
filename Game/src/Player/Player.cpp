#include <cmath>
#include <iostream>

#include "player/Player.h"
#include "Camera2d.h"
#include "Global.h"
#include "Configuration.h"
#include "Collision.h"
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

	bind(Configuration::PlayerInputs::Shoot, [this](const sf::Event&)
	{
			Shoot();
	});

	_sprite.setTextureRect(sf::IntRect(597, 0, 199, 210.5f));
	setGridPosition(Configuration::getInitialPos());
    _position = Configuration::getInitialPos();

	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2.f);

	setPosition(_world.getWidth() / 2 + 240, _world.getHeight() / 2 + 370);

	_camera = std::make_unique<Camera2d>(_world, _position, _direction, sf::Vector2f(_size_f, _size_f), _plane);
}

bool Player::isCollide(const Entity& other) const
{
	return false;
}

void Player::update(sf::Time deltaTime)
{

	float seconds = deltaTime.asSeconds();
   
	_timeSinceLastShoot += deltaTime;

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
	setGridPosition(_position);
	float rotation = 0;
	if (_rotateDirection != 0.0f)
	{
		 rotation = _rotationSpeed * _rotateDirection * seconds;
	}

	
	_camera->Raycasting(rotation);
}

void Player::processEvents()
{
	_rotateDirection = 0.0f;
	_moveForward = 0.0f;
	ActionTarget::processEvents();
}

void Player::Shoot()
{
	if (_timeSinceLastShoot > sf::seconds(0.5))
	{
		std::cout << "Shoot" << std::endl;
		_timeSinceLastShoot = sf::Time::Zero;
	}
	
}

void Player::onDestroy()
{
	Entity::onDestroy();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	_camera->draw(target, states);
	Entity::draw(target, states);
	
}