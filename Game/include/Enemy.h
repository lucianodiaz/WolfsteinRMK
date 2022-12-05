#pragma once
#include "Actor.h"
class Enemy : public Actor
{
public:
	Enemy(Configuration::Textures texId, World& world);

	virtual bool isCollide(const Entity& other) const override;

	virtual void update(sf::Time deltaTime) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

