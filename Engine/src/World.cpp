#include "World.h"

World::World(float x, float y) : _x(x),_y(y)
{
}

World::~World()
{
}

int World::getX()const
{
    return _x;
}

int World::getY()const
{
    return _y;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
