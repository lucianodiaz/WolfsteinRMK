#include "gameScenes/SceneGame.h"
#include "Configuration.h"
#include "World.h"
#include "Player/Player.h"
#include "Actor.h"


SceneGame::SceneGame(SceneStateMachine& ssm, Window& window, World& world) :
	_world(world), _window(window), _sceneStateMachine(ssm),_switchToState(0)
{
	
}

void SceneGame::onCreate()
{
	
}

void SceneGame::onDestroy()
{
}

void SceneGame::onActivate()
{
	_world.loadMap(Configuration::Images::TestMap);
}

void SceneGame::onDeactivate()
{
	std::cout << "onDeactive" << std::endl;
}

void SceneGame::setSwitchToScene(unsigned int id)
{
	_switchToState = id;
}

void SceneGame::processInput()
{
	sf::Event evt;
	while (_window.pollEvent(evt))
	{
		if (evt.type == sf::Event::Closed)
			_window.close();
		if (evt.type == sf::Event::KeyPressed)
		{
			if (evt.key.code == sf::Keyboard::Escape)
			{
				_sceneStateMachine.switchTo(_switchToState);
			}
		}
		if(Configuration::player!= nullptr)
		Configuration::player->processEvent(evt);
	}
	if (Configuration::player != nullptr)
	Configuration::player->processEvents();
}

void SceneGame::update(sf::Time deltaTime)
{
	_world.update(deltaTime);
	if (Configuration::player == nullptr)
	{
		//auto pl = new Player(_world);
		Configuration::player = new Player(_world);
		_world.add(Configuration::player);
	}

	if (Configuration::isGameOver())
	{
		_sceneStateMachine.switchTo(_switchToState);
	}
}

void SceneGame::draw(Window& window)
{
	window.draw(_world);
}
