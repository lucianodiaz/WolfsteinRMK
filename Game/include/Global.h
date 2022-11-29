#pragma once

#define BLACK sf::Color(0,0,0)
#define BLUE sf::Color(0,0,255)
#define RED sf::Color(255,0,0)
#define GREY sf::Color(28,28,28)
#define BROWN sf::Color(170,85,0)
#define BLACKRED sf::Color(100,0,0)
#define YELLOW sf::Color(255,255,0)
#define CYAN sf::Color(0,255,255)

#define GREEN sf::Color(0,255,0)

constexpr float PI = 3.141592653589793116f;
constexpr int MAP_HEIGHT = 52;
constexpr int MAP_WIDTH = 52;

const int texture_size = 512;
const int texture_wall_size = 64;


enum Cell
{
	Empty,
	Black,
	Blue,
	Red,
	Green,
	Brown,
	BlackRed,
	Grey,
	Yellow,
	Cyan
};