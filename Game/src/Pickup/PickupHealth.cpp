#include "Pickup/PickupHealth.h"
#include "Collision.h"

PickupHealth::PickupHealth(Configuration::Textures tex_id, World& world) : Actor(tex_id,world)
{
    _ammountHealth = 10;
}

bool PickupHealth::isCollide(const Entity& other) const
{
    return Collision::collisionEntity(*this);
}

void PickupHealth::update(sf::Time deltaTime)
{
    Actor::update(deltaTime);

    if (Configuration::player != nullptr)
    {
        if (isCollide(*Configuration::player))
        {
            _alive = false;
            Configuration::player->getHealth(_ammountHealth);
        }
    }
}

void PickupHealth::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Actor::draw(target, states);
}
