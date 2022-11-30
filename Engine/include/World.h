#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <memory>
#include "Configuration.h"

class Entity;
class Map;
class World : public sf::Drawable
{
public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	World(float x, float y);
	virtual ~World();

	void update(sf::Time deltaTime);

	void add(Entity* entity);

	void clear();

	int getWidth()const;
	int getHeight()const;

	void loadMap(Configuration::Images mapId);

	Map& getMap()const { return *_currMap; }
	const std::list<Entity*> getEntities() const;

private:
	std::list<Entity*> _entities;
	std::list<Entity*> _entitiesTmp;
	std::list<std::unique_ptr<sf::Sound>> _sounds;

	std::unique_ptr<Map> _currMap;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	const int _x;
	const int _y;
};

