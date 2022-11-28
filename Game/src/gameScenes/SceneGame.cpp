#include "gameScenes/SceneGame.h"
#include "Configuration.h"
#include "World.h"
#include "Player/Player.h"


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
		Configuration::player->setPosition(_world.getX() / 2, _world.getY() / 2 + 270);
		_world.add(Configuration::player);
	}
}

void SceneGame::draw(Window& window)
{
	window.draw(_world);
}
