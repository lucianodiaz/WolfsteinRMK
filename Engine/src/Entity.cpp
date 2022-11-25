#include "Entity.h"
#include "World.h"

Entity::Entity(World& world) : _world(world)
{
}

Entity::~Entity()
{
}

const sf::Vector2f& Entity::getPosition() const
{
	return _sprite.getPosition();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
