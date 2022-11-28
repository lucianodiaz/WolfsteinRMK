#pragma once

#define BLACK sf::Color(0,0,0)
#define BLUE sf::Color(0,0,255)
#define RED sf::Color(255,0,0)
#define GREEN sf::Color(0,255,0)
#define BROWN sf::Color(170,85,0)

constexpr float PI = 3.141592653589793116f;
constexpr int MAP_HEIGHT = 73;
constexpr int MAP_WIDTH = 74;

const int texture_size = 512;
const int texture_wall_size = 64;


enum Cell
{
	Empty,
	Black,
	Blue,
	Red,
	Green,
	Brown
};