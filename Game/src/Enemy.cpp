
#include "Enemy.h"
#include "Collision.h"
#include <iostream>

Enemy::Enemy(Configuration::Textures texId, World& world) : Actor(texId,world)
{
}

bool Enemy::isCollide(const Entity& other) const
{
    return Collision::collisionEntity(*this);
}

void Enemy::update(sf::Time deltaTime)
{
	Actor::update(deltaTime);

    if (Configuration::player != nullptr)
    {
        if (isCollide(*Configuration::player))
        {
            std::cout << "is collide with player" << std::endl;
        }
       
    }


    float seconds = deltaTime.asSeconds();
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
