#include "Configuration.h"

ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::Music, int>Configuration::musics;
ResourceManager<sf::Texture, int>Configuration::textures;
ResourceManager<sf::Image, int>Configuration::images;

ActionMap<int> Configuration::guiInputs;
ActionMap<int> Configuration::playerInputs;

void Configuration::initialize()
{
	initFonts();
	initMusics();
	initTextures();
	initGuiInputs();
}

void Configuration::initTextures()
{
	textures.load(Textures::TittleScreenImage, "assets/images/tittleScreen.jpg");
	textures.load(Textures::MenuImage, "assets/images/menu.png");
	images.load(Images::icon, "assets/images/icon/icon.png");
}

void Configuration::initMusics()
{
	musics.load(Music::MainMenu, "assets/music/MainMenu.ogg");
	musics.load(Music::TittleScreen, "assets/music/TittleScreen.ogg");
	musics.load(Music::EndLevel, "assets/music/EndLevel.ogg");
	musics.load(Music::Level1, "assets/music/Level1.ogg");
}

void Configuration::initFonts()
{
	fonts.load(Fonts::Leaderboard, "assets/fonts/Arcade.ttf");
	fonts.load(Fonts::Desc, "assets/fonts/league.ttf");
	fonts.load(Fonts::GUI, "assets/fonts/retro.ttf");
}

void Configuration::initGuiInputs()
{
	guiInputs.map(GuiInputs::Escape, Action(sf::Keyboard::Escape, Action::Type::Pressed));
}

void Configuration::initPlayerInputs()
{
	playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::W, Action::Type::Pressed));
	playerInputs.map(PlayerInputs::Down, Action(sf::Keyboard::S, Action::Type::Pressed));
	playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::A, Action::Type::Pressed));
	playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::D, Action::Type::Pressed));
}
