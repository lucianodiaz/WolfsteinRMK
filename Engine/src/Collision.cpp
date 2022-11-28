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
	// create the corners of the rectangle
	sf::Vector2i upper_left(pos - size / 2.0f);
	sf::Vector2i lower_right(pos + size / 2.0f);
	if (upper_left.x < 0 || upper_left.y < 0 || lower_right.x >= MAP_WIDTH || lower_right.y >= MAP_HEIGHT) {
		return false; // out of map bounds
	}
	// loop through each map tile within the rectangle. The rectangle could be multiple tiles in size!
	for (int y = upper_left.y; y <= lower_right.y; ++y) {
		for (int x = upper_left.x; x <= lower_right.x; ++x) {
			if (map.getTile(x, y) != Cell::Empty) {
				return false;
			}
		}
	}
	return true;
}