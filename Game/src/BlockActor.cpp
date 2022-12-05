#include "BlockActor.h"
#include "Collision.h"

BlockActor::BlockActor(Configuration::Textures tex_id, World& world) : Actor(tex_id,world)
{
	_collide = true;
}

bool BlockActor::isCollide(const Entity& other) const
{
	return Collision::collisionEntity(other);
}

void BlockActor::update(sf::Time deltaTime)
{
}

void BlockActor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Actor::draw(target, states);
}
