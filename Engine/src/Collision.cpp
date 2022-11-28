#include "Collision.h"
#include "Entity.h"
#include "Global.h"
#include "Map.h"

bool Collision::circleTest(const sf::Sprite& first, const sf::Sprite& second)
{
    sf::Vector2f first_rect(first.getTextureRect().width, first.getTextureRect().height);
    first_rect.x *= first.getScale().x;
    first_rect.y *= first.getScale().y;

    sf::Vector2f second_rect(second.getTextureRect().width, second.getTextureRect().height);
    second_rect.x *= second.getScale().x;
    second_rect.y *= second.getScale().y;

    float radius1 = (first_rect.x + first_rect.y) / 4;
    float radius2 = (second_rect.x + second_rect.y) / 4;

    float xd = first.getPosition().x - second.getPosition().x;
    float yd = first.getPosition().y - second.getPosition().y;

    return std::sqrt(xd * xd + yd * yd) <= radius1 + radius2;
}

bool Collision::canMove(sf::Vector2f pos, sf::Vector2f size, Map& map)
{
	bool res = true;
	sf::Vector2i upperLeft(pos - size / 2.0f);
	sf::Vector2i lowerRight(pos + size / 2.0f);

	if (upperLeft.x < 0 || upperLeft.y < 0 ||
		lowerRight.x >= MAP_WIDTH || lowerRight.y >= MAP_HEIGHT)
	{
		res = false;
	}

	return res;
}

bool Collision::mapCollision(float _x,float _y, Map& map)
{
    float cellX = _x/ CELL_SIZE;
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
			if (Cell::Wall == map.getMap()[x][y])
			{
				return true;
			}
		}
	}
	return false;
}
