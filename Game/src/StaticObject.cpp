#include "StaticObject.h"

StaticObject::StaticObject(Configuration::Textures texId, World& world) : Entity(texId , world)
{
}

bool StaticObject::isCollide(const Entity& other) const
{
    return false;
}

void StaticObject::update(sf::Time deltaTime)
{
}
