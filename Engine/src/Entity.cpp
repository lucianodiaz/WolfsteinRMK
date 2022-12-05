#include "Entity.h"


Entity::Entity(Configuration::Textures tex_id, World& world):_world(world),_alive(true)
{
	_alive = true;
	sf::Texture& texture = Configuration::textures.get(tex_id);
	_texture = texture;
	_sprite.setTexture(texture);
	_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

Entity::~Entity()
{
}

void Entity::setGridPosition(float x, float y)
{
	_position = sf::Vector2f(x, y);
	
}

void Entity::setGridPosition(sf::Vector2f pos)
{
	_position = pos;
}

const sf::Vector2f& Entity::getGridPosition() const
{
	return _position;
	// // O: insert return statement here
}

const sf::Vector2f& Entity::getPosition() const
{
	return _sprite.getPosition();
}

bool Entity::isAlive() const
{
	return _alive;
}

void Entity::onDestroy()
{
	_alive = false;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
