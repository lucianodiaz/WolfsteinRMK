#include "Map.h"


Map::Map()
{
}

void Map::loadLevel(Configuration::Images tex_id)
{
	sf::Image mapSketch = Configuration::images.get(tex_id);

	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			_map[a][b] = Cell::Empty;

		}
	}

	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			sf::Color pixel = mapSketch.getPixel(a, b);

			if (pixel == BLACK)
			{
				_map[a][b] = Cell::Wall;
			}
			else
			{
				_map[a][b] = Cell::Empty;
			}
		}
	}
}

Cell Map::getTile(int _x, int _y) const
{
	//return _map[x-1][y-1];
	float cellX = _x / CELL_SIZE;
	float cellY = _y / CELL_SIZE;

	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0:
		{
			x = static_cast<short>(floor(cellX));
			y = static_cast<short>(floor(cellY));

			break;
		}
		case 1:
		{
			x = static_cast<short>(ceil(cellX));
			y = static_cast<short>(floor(cellY));

			break;
		}
		case 2:
		{
			x = static_cast<short>(floor(cellX));
			y = static_cast<short>(ceil(cellY));

			break;
		}
		case 3:
		{
			x = static_cast<short>(ceil(cellX));
			y = static_cast<short>(ceil(cellY));
		}
		}
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
			return _map[x][y];
		}
	}
}

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> Map::getMap() const
{
	return _map;
}
