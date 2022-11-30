#include "Map.h"
#include "StaticObject.h"


Map::Map(World& world) : _world(world)
{
}

void Map::loadLevel(Configuration::Images tex_id)
{
	sf::Image mapSketch = Configuration::images.get(tex_id);

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
			else if (pixel == LIGHTGREEN)
			{
				StaticObject* obj = new StaticObject(Configuration::Textures::GreenLight,_world);
				obj->setGridPosition(a, b);
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

std::vector<StaticObject*> Map::getSprites()const
{
	return _sprites;
}
