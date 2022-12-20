#pragma once
#include "Actor.h"

class AnimationManager;

class Enemy : public Actor
{
public:
	enum class States
	{
		Idle,
		Walking,
		Hit,
		Death
	};
	Enemy(Configuration::Textures texId, World& world);

	virtual bool isCollide(const Entity& other) const override;

	virtual void update(sf::Time deltaTime) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void receiveDamage(float dmg);
	std::unique_ptr<AnimationManager> _animationManager;
private:

	void animationSetup();
	States _currentState;
	sf::Time _timeSinceLastShoot;

	float _health;
};

