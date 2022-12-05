#include <cmath>
#include <iostream>

#include "player/Player.h"
#include "AnimationManager.h"
#include "Camera2d.h"
#include "Configuration.h"
#include "Collision.h"
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

	bind(Configuration::PlayerInputs::Shoot, [this](const sf::Event&)
	{
			Shoot();
	});
	setGridPosition(Configuration::getInitialPos());
    _position = Configuration::getInitialPos();

	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2.f);
	_sprite.setScale(2.5, 2.5);
	setPosition(_world.getWidth()/2 + 232 , _world.getHeight());
	_health = 100;
	_camera = std::make_unique<Camera2d>(_world, _position, _direction, sf::Vector2f(_size_f, _size_f), _plane);

	_animationManager = std::make_unique<AnimationManager>(&_texture, sf::Vector2u(4, 2), 0.1f);
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

	_animationManager->update(0, deltaTime);
	_sprite.setTextureRect(_animationManager->uvRect);
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
		
		_animationManager->playAnimation();
		_isShooting = true;
		std::cout << "Shoot" << std::endl;
		_timeSinceLastShoot = sf::Time::Zero;

		
	}
	
}

void Player::receiveDamage(float dmg)
{
	_health = std::clamp((_health - dmg), 0.0f, 100.0f);
}

void Player::getHealth(float heal)
{
	_health = std::clamp(_health + heal,0.0f,100.0f);
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