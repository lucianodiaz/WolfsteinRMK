#pragma once
#include <array>
#include <unordered_map>
#include "Configuration.h"
#include "Global.h"
#include "World.h"

class Map
{
public:

	Map();

	void loadLevel(Configuration::Images tex_id);

	Cell getTile(int x, int y)const;
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> getMap()const;
    enum class WallTexture {
        Smiley,
        Red,
        Bush,
        Sky,
        Pink,
        Wallpaper,
        Dirt,
        Exit,
    };
    const std::unordered_map<char, WallTexture> wallTypes{
    {Cell::Wall, WallTexture::Pink},
    //{Cell::Wall, WallTexture::Dirt},
    //{Cell::Wall, WallTexture::Wallpaper},
    //{Cell::Wall, WallTexture::Bush},
    //{Cell::Wall, WallTexture::Sky},
    //{Cell::Wall, WallTexture::Red},
    //{Cell::Wall, WallTexture::Smiley},
    //{Cell::Wall, WallTexture::Exit},
    };
private:
	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> _map;
};

