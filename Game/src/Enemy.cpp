
#include <iostream>
#include "AnimationManager.h"
#include "Collision.h"
#include "Enemy.h"



Enemy::Enemy(Configuration::Textures texId, World& world) : Actor(texId,world)
{
    _health = 25;
    _animationManager = std::make_unique<AnimationManager>(&_texture, sf::Vector2u(4, 3),.3f);

    Animation idleAnimation;
    idleAnimation.nameAnimation = (int)states::Idle;
    idleAnimation.row = 2;
    idleAnimation.duration = .2f;
    idleAnimation.cantFrame = 4;
    idleAnimation.startIndex = 0;
    idleAnimation.loop = true;
    idleAnimation.repeat = false;
    _animationManager->addAnimation(idleAnimation);
    

    _sprite.setTextureRect(_animationManager->uvRect);
}

bool Enemy::isCollide(const Entity& other) const
{
    return Collision::collisionEntity(*this);
}

void Enemy::update(sf::Time deltaTime)
{
   
	Actor::update(deltaTime);
    float seconds = deltaTime.asSeconds();
    _animationManager->playAnimation((int)states::Idle);
  
    //_animationManager->update(3, deltaTime);
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
    _animationManager->update(0, deltaTime);
   // _sprite.setTextureRect(_animationManager->uvRect);

    //if (getGridPosition().x < _initialPosition.x + 2)
    //{
    //    setGridPosition(getGridPosition().x + 1.1 * seconds, getGridPosition().y);
    //}
    //else
    //{
    //    setGridPosition(_initialPosition);
    //}

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Actor::draw(target, states);
    target.draw(_spriteLines, &_texture);
}

void Enemy::receiveDamage(float dmg)
{
    _health = std::clamp(_health - dmg,0.0f,100.f);
}
