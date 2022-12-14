#include "Map.h"
#include "Actor.h"
#include "Enemy.h"
#include "BlockActor.h"
#include "Pickup/PickupKey.h"

Map::Map(World& world) : _world(world)
{
}

void Map::clear()
{
	_sprites.clear();
	_cellMap.clear();
}

void Map::loadLevel(Configuration::Images tex_id)
{
	sf::Image mapSketch = Configuration::images.get(tex_id);

	_cellMap.clear();
	_sprites.clear();

	_cellMap = std::vector(MAP_WIDTH * MAP_HEIGHT,Cell::Empty);
	for (int a = 0; a < MAP_WIDTH; a++)
	{
		for (int b = 0; b < MAP_HEIGHT; b++)
		{
			sf::Color pixel = mapSketch.getPixel(a, b);
			if (pixel == BLACK)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Black;
			}
			else if (pixel == BROWN)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Brown;
			}
			else if (pixel == BLUE)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Blue;
			}
			else if (pixel == RED)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Red;
			}
			else if (pixel == BLACKRED)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::BlackRed;
			}
			else if (pixel == YELLOW)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Yellow;
			}
			else if (pixel == CYAN)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Cyan;
			}
			else if (pixel == GREY)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Grey;
			}
			else if (pixel == PURPLE)
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Purple;
			}
			else if (pixel == YELLOWKEY)
			{
				Actor* obj = new PickupKey(Configuration::Textures::Key, _world);
				obj->setGridPosition(a, b);
				_world.add(obj);
				_sprites.emplace_back(obj);
			}
			else if (pixel == LIGHTBROWN)
			{
				Actor* obj = new BlockActor(Configuration::Textures::Barrel, _world);
				obj->setGridPosition(a, b);
				_world.add(obj);
				_sprites.emplace_back(obj);
			}
			else if (pixel == LIGHTGREEN)
			{
				Actor* obj = new Actor(Configuration::Textures::GreenLight, _world);
				obj->setGridPosition(a, b);
				_world.add(obj);
				_sprites.emplace_back(obj);
			}
			else if (pixel == LIGHTRED)
			{
 				Actor* obj = new Enemy(Configuration::Textures::Guard, _world);
				obj->setGridPosition(a, b);
				obj->_initialPosition = sf::Vector2f(a, b);
				_world.add(obj);
				_sprites.emplace_back(obj);
			}
			else if (pixel == GREEN)
			{
				Configuration::setInitialPosition(sf::Vector2f(a, b));
			}
			else
			{
				_cellMap.at(b * MAP_WIDTH + a) = Cell::Empty;
			}

		}
	}

}

Cell Map::getTile(int x, int y) const
{
	return _cellMap.at(y * MAP_WIDTH + x);//[y * MAP_WIDTH + x];
}

std::vector<Actor*> Map::getSprites()const
{
	return _sprites;
}
