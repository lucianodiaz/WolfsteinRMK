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
        Flag,//blackRed
        Brick,//Red
        Moo,//cyan
        Stone,//black
        BlueStone,//Blue
        MooStone,//yellow
        Wood,//brown
        Refined,//grey
    };
    const std::unordered_map<char, WallTexture> wallTypes{
    {Cell::Blue, WallTexture::BlueStone},
    {Cell::Black, WallTexture::Stone},
    {Cell::Brown, WallTexture::Wood},
    {Cell::Red, WallTexture::Brick},
    {Cell::BlackRed, WallTexture::Flag},
    {Cell::Cyan, WallTexture::Moo},
    {Cell::Yellow, WallTexture::MooStone},
    {Cell::Grey, WallTexture::Refined},
    };
private:
    std::vector<Cell> _cellMap;
};

