#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourceManager.h"
#include "Input/ActionMap.h"

class Configuration
{
public:
	Configuration() = delete;
	Configuration(const Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;
	
	enum PlayerInputs : int
	{
		Up,
		Down,
		Right,
		Left
	};
	static ActionMap<int> playerInputs;

	enum GuiInputs : int
	{
		Escape
	};
	static ActionMap<int> guiInputs;

	enum Fonts : int {Leaderboard,Desc,GUI};
	static ResourceManager<sf::Font> fonts;

	enum Textures : int
	{
		Player,
		WeakEnemy,
		Walls,
		TittleScreenImage,
		MenuImage
	};
	static ResourceManager<sf::Texture> textures;

	enum Images : int
	{
		icon
	};
	static ResourceManager<sf::Image> images;
	enum Music : int
	{
		TittleScreen,
		MainMenu,
		EndLevel,
		Level1
	};
	static ResourceManager < sf::Music > musics;

	static void initialize();

private:
	static void initTextures();
	static void initMusics();
	static void initFonts();
	static void initGuiInputs();
	static void initPlayerInputs();
};

