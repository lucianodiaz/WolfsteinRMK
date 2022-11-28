#include "Map.h"


Map::Map()
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