#include "Configuration.h"

ResourceManager<sf::Font, int> Configuration::fonts;
ResourceManager<sf::Music, int>Configuration::musics;
ResourceManager<sf::Texture, int>Configuration::textures;
ResourceManager<sf::Image, int>Configuration::images;

ActionMap<int> Configuration::guiInputs;
ActionMap<int> Configuration::playerInputs;


int Configuration::_score;
int Configuration::lives;

sf::Vector2f Configuration::_initialPosition;

Player* Configuration::player = nullptr;

void Configuration::initialize()
{
	initFonts();
	initMusics();
	initTextures();
	initPlayerInputs();
	initGuiInputs();
}

const sf::Vector2f Configuration::getInitialPos()
{
	return _initialPosition;
}
void Configuration::setInitialPosition(sf::Vector2f pos)
{
	_initialPosition = pos;
}
void Configuration::draw(sf::RenderTarget& target)
{
}

void Configuration::initTextures()
{
	textures.load(Textures::PlayerTexture, "assets/player/player.png");
	textures.load(Textures::TittleScreenImage, "assets/images/tittleScreen.jpg");
	textures.load(Textures::MenuImage, "assets/images/menu.png");
	textures.load(Textures::Walls, "assets/maps/walls.png");
	textures.load(Textures::WolfTextures, "assets/maps/wolftextures.png");

	textures.load(Textures::Barrel, "assets/statics/barrel.png");
	textures.load(Textures::GreenLight, "assets/statics/greenlight.png");
	textures.load(Textures::Pillar, "assets/statics/pillar.png");

	images.load(Images::icon, "assets/images/icon/icon.png");
	images.load(Images::TestMap, "assets/maps/level1.png");
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
	playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::W));
	playerInputs.map(PlayerInputs::Down, Action(sf::Keyboard::S));
	playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::A));
	playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::D));
}
