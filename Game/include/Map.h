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
    enum class WallTexture {
        Flag,
        Brick,
        Moo,
        Stone,
        BlueStone,
        MooStone,
        Wood,
        Refined,
    };
    const std::unordered_map<char, WallTexture> wallTypes{
    {Cell::Blue, WallTexture::BlueStone},
    {Cell::Black, WallTexture::Stone},
    {Cell::Brown, WallTexture::Wood},
    //{Cell::Wall, WallTexture::Bush},
    //{Cell::Wall, WallTexture::Sky},
    //{Cell::Wall, WallTexture::Red},
    //{Cell::Wall, WallTexture::Smiley},
    //{Cell::Wall, WallTexture::Exit},
    };
private:
    std::vector<Cell> _cellMap;
};

