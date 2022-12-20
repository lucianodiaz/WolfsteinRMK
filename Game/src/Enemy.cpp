
#include <iostream>
#include "AnimationManager.h"
#include "Collision.h"
#include "Enemy.h"



Enemy::Enemy(Configuration::Textures texId, World& world) : Actor(texId,world)
{
    _health = 25;
    _animationManager = std::make_unique<AnimationManager>(&_texture, sf::Vector2u(4, 3));
    _currentState = States::Idle;

    animationSetup();
    _animationManager->playAnimation((int)_currentState);
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
    _animationManager->playAnimation((int)_currentState);
  
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
    _animationManager->update(deltaTime);

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

void Enemy::animationSetup()
{
    Animation idleAnimation;
    idleAnimation.nameAnimation = (int)States::Idle;
    idleAnimation.row = 3;
    idleAnimation.duration = .9f;
    idleAnimation.cantFrame = 1;
    idleAnimation.startIndex = 1;
    idleAnimation.loop = false;
    idleAnimation.repeat = true;
    _animationManager->addAnimation(idleAnimation);
    _animationManager->addOnComplete(idleAnimation.nameAnimation, [this]() {/*_alive = false;*/_currentState = States::Hit; });

    Animation walkAnimation;
    walkAnimation.nameAnimation = (int)States::Walking;
    walkAnimation.row = 1;
    walkAnimation.duration = .2f;
    walkAnimation.cantFrame = 4;
    walkAnimation.startIndex = 0;
    walkAnimation.loop = true;
    walkAnimation.repeat = true;
    _animationManager->addAnimation(walkAnimation);
    _animationManager->addOnComplete(walkAnimation.nameAnimation, [this]() {/*_alive = false;*/ });

    Animation hitAnimation;
    hitAnimation.nameAnimation = (int)States::Hit;
    hitAnimation.row = 3;
    hitAnimation.duration =.2f;
    hitAnimation.cantFrame = 1;
    hitAnimation.startIndex = 0;
    hitAnimation.loop = true;
    hitAnimation.repeat = true;
    _animationManager->addAnimation(hitAnimation);
    _animationManager->addOnComplete(hitAnimation.nameAnimation, [this]() {/*_alive = false;*/_currentState = States::Idle; });

    Animation deathAnimation;
    deathAnimation.nameAnimation = (int)States::Death;
    deathAnimation.row = 2;
    deathAnimation.duration = .2f;
    deathAnimation.cantFrame = 4;
    deathAnimation.startIndex = 0;
    deathAnimation.loop = false;
    deathAnimation.repeat = false;
    _animationManager->addAnimation(deathAnimation);
    _animationManager->addOnComplete(deathAnimation.nameAnimation, [this]() {/*_alive = false;*/ _currentState = States::Idle;});


}
