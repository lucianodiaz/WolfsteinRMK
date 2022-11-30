#pragma once
#include "Entity.h"

class StaticObject : public Entity, sf::NonCopyable
{
public:
	StaticObject(Configuration::Textures texId, World& world);

	virtual bool isCollide(const Entity& other) const override;

	virtual void update(sf::Time deltaTime) override;
};

