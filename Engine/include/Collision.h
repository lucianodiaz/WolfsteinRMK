#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class Map;

class Collision
{
public:

	Collision() = delete;
	Collision(const Collision&) = delete;
	Collision& operator=(const Collision&) = delete;

	static bool overlapEntity(const Entity& entity, const Entity& other);
	static bool collisionEntity(const Entity& entity);
	static bool circleTest(const sf::Sprite& first, const sf::Sprite& second);
	static bool canMove(sf::Vector2f pos, sf::Vector2f size, Map& map);
};

