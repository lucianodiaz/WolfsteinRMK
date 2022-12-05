#include "Pickup/PickupKey.h"
#include "Collision.h"
PickupKey::PickupKey(Configuration::Textures tex_id, World& world) : Actor(tex_id,world)
{
}
bool PickupKey::isCollide(const Entity& other) const
{
	return Collision::collisionEntity(*this);
}

void PickupKey::update(sf::Time deltaTime)
{
	Actor::update(deltaTime);
	if (Configuration::player != nullptr)
	{
		if (isCollide(*Configuration::player))
		{
			_alive = false;
			Configuration::player->setKey(true);
		}
	}
}

void PickupKey::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Actor::draw(target, states);
}
