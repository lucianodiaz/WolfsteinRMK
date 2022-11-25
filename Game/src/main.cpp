#include "Game.h"
#include "Configuration.h"

int main()
{
    Configuration::initialize();
    Game game;

    game.run();
    return 0;
}