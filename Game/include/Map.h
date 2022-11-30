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
        Stone = 0,//black
        Stone2 = 1,
        StoneFlag2 = 2,
        StoneHittler = 3,
        EmptyJail = 4,
        EagleStone = 5,
        Jail = 6,
        BlueStone2 = 7,
        BlueStone = 8,//Blue
        EagleWood = 9,
        HittlerWood = 10,
        Wood = 11,//brown
        MetalDoor = 12,
        MetalWallDesc = 13,
        MetalWall = 14,
        Landscape = 15,
        Brick = 16,
        BrickCross = 17,
        Mod = 18,//cyan 
        Flag = 19,//blackRed
        MooStone,//yellow
        Refined,//grey
    };
    const std::unordered_map<char, WallTexture> wallTypes{
    {Cell::Blue, WallTexture::BlueStone},
    {Cell::Black, WallTexture::Stone},
    {Cell::Brown, WallTexture::Wood},
    {Cell::Red, WallTexture::Brick},
    {Cell::BlackRed, WallTexture::Flag},
    {Cell::Cyan, WallTexture::Mod},
    {Cell::Yellow, WallTexture::MooStone},
    {Cell::Grey, WallTexture::Refined},
    };
private:
    std::vector<Cell> _cellMap;
};

