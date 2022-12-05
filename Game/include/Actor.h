#pragma once
#include "Entity.h"
#include "Player/Player.h"

class Actor : public Entity, sf::NonCopyable
{
public:
	Actor(Configuration::Textures texId, World& world);

	virtual bool isCollide(const Entity& other) const override;

	virtual void update(sf::Time deltaTime) override;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool isBlock()const { return _collide; }
	sf::Texture getTexture()const;
	sf::VertexArray _spriteLines;
	sf::Vector2f _initialPosition;

protected:
	bool _collide{};
};

