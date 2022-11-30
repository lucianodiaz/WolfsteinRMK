#include "World.h"
#include "Entity.h"
#include "Map.h"

World::World(float x, float y) : _x(x),_y(y)
{
    _currMap = std::make_unique<Map>(*this);
}

World::~World()
{
}

void World::update(sf::Time deltaTime)
{
    if (_entitiesTmp.size() > 0)
    {
        _entities.splice(_entities.end(), _entitiesTmp);
    }

	for (Entity* entity_ptr : _entities)
	{
		Entity& entity = *entity_ptr;

        if (entity.isAlive())
        {
            entity.update(deltaTime);
        }
		
	}
    for (auto it = _entities.begin(); it != _entities.end();)
    {
        if (not (*it)->isAlive())
        {
            delete* it;
            it = _entities.erase(it);
        }
        else
            ++it;
    }
   
    /*const auto end = _entities.end();
    for (auto it_i = _entities.begin(); it_i != end; ++it_i)
    {
        if ()
            Entity& entity_i = **it_i;
            auto it_j = it_i;
            it_j++;

            for (; it_j != end; ++it_j)
            {
                Entity& entity_j = **it_j;

            }
    }*/
}

void World::add(Entity* entity)
{
    _entitiesTmp.emplace_back(entity);
}

void World::clear()
{
    for (Entity* entity : _entities)
    {
        delete entity;
    }
    _entities.clear();
    for (Entity* entity : _entitiesTmp)
    {
        delete entity;
    }
    _entitiesTmp.clear();
}

int World::getWidth()const
{
    return _x;
}

int World::getHeight()const
{
    return _y;
}

const std::list<Entity*> World::getEntities() const
{
    return _entities;
}

void World::loadMap(Configuration::Images mapId)
{
    _currMap->loadLevel(mapId);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (Entity* entity : _entities)
    {
        target.draw(*entity, states);
    }

   
}
