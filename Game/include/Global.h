#pragma once

#define BLACK sf::Color(0,0,0)
#define BLUE sf::Color(0,0,255)
#define RED sf::Color(255,0,0)
#define GREEN sf::Color(0,255,0)

constexpr float PI = 3.141592653589793116f;
constexpr unsigned char CELL_SIZE = 1;
constexpr unsigned char MAP_HEIGHT = 24;
constexpr unsigned char MAP_WIDTH = 40;

const int texture_size = 512;
const int texture_wall_size = 128;


enum Cell
{
	Empty,
	Wall
};