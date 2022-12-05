
#include "Enemy.h"
#include "Collision.h"
#include <iostream>

Enemy::Enemy(Configuration::Textures texId, World& world) : Actor(texId,world)
{
    _health = 25;
}

bool Enemy::isCollide(const Entity& other) const
{
    return Collision::collisionEntity(*this);
}

void Enemy::update(sf::Time deltaTime)
{
	Actor::update(deltaTime);
    float seconds = deltaTime.asSeconds();
    _timeSinceLastShoot += deltaTime;
    if (Configuration::player != nullptr)
    {
        if (isCollide(*Configuration::player))
        {
			if (_timeSinceLastShoot > sf::seconds(0.5))
			{
                std::cout << "is collide with player" << std::endl;
                Configuration::player->receiveDamage(10.f);
				_timeSinceLastShoot = sf::Time::Zero;
			}
            
        }
       
    }


    
    if (getGridPosition().x < _initialPosition.x + 2)
    {
        setGridPosition(getGridPosition().x + 1.1 * seconds, getGridPosition().y);
    }
    else
    {
        setGridPosition(_initialPosition);
    }

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Actor::draw(target, states);
}

void Enemy::receiveDamage(float dmg)
{
    _health = std::clamp(_health - dmg,0.0f,100.f);
}
