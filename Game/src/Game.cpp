#include "Configuration.h"
#include "Game.h"
#include "Window.h"
#include "gameScenes/SceneMainMenu.h"
#include "gameScenes/SceneSplashScreen.h"

Game::Game(int x, int y) : _window(std::make_unique<Window>(x,y,"Wolfenstein3d RMK")),
							_world(x,y)
{
	std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(sceneStateMachine, *_window);

	std::shared_ptr<SceneMainMenu> menuScene = std::make_shared<SceneMainMenu>(sceneStateMachine, *_window);

	unsigned int splashScreenID = sceneStateMachine.add(splashScreen);
	unsigned int menuSceneID = sceneStateMachine.add(menuScene);

	splashScreen->setSwitchToScene(menuSceneID);

	sceneStateMachine.switchTo(splashScreenID);

	_window->getRenderWindow().setIcon(Configuration::images.get(Configuration::Images::icon).getSize().x,
		Configuration::images.get(Configuration::Images::icon).getSize().y, Configuration::images.get(Configuration::Images::icon).getPixelsPtr());
}

Game::~Game()
{
	std::cout << "OnDestroy Game" << std::endl;
}

void Game::run(int frame_per_seconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	sf::Time TimerPerFrame = sf::seconds(1.f / frame_per_seconds);

	while (_window->isOpen())
	{
		processEvents();
		bool repaint = false;
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimerPerFrame)
		{
			timeSinceLastUpdate -= TimerPerFrame;
			repaint = true;
			update(TimerPerFrame);
		}

		if (repaint)draw();
	}
}

void Game::update(sf::Time deltaTime)
{
	sceneStateMachine.update(deltaTime);
}

void Game::draw()
{
	_window->clear();
	sceneStateMachine.draw(*_window);
	_window->display();
}

void Game::processEvents()
{
	sf::Event evt;
	sceneStateMachine.processInput();
	/*while (_window->pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			_window->close();
		else if (evt.type == sf::Event::KeyPressed)
		{
			if (evt.key.code == sf::Keyboard::Escape)
			{
				_window->close();
			}
		}
	}*/

}
