#include "Actor.h"
#include "Camera2d.h"
#include "Configuration.h"
#include "Map.h"
#include "World.h"
#include "gameScenes/SceneGame.h"
#include "Player/Player.h"

SceneGame::SceneGame(SceneStateMachine& ssm, Window& window, World& world) :
	_world(world), _window(window), _sceneStateMachine(ssm),_switchToState(0),_objective2(window.getRenderWindow()),
	_objective1(window.getRenderWindow())
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

	initGUI();
	Configuration::musics.get(Configuration::Music::Level1).setLoop(true);
	Configuration::musics.get(Configuration::Music::Level1).play();
	Configuration::musics.get(Configuration::Music::Level1).setVolume(0.5);

}

void SceneGame::onDeactivate()
{
	std::cout << "onDeactivate:: SCENEGAME" << std::endl;
	Configuration::musics.get(Configuration::Music::Level1).stop();
	Configuration::player->getCamera().restart();
	_world.clear();
	_world.getMap().clear();
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
		Configuration::reset();
		_sceneStateMachine.switchTo(_switchToState);

	}
}

void SceneGame::draw(Window& window)
{
	window.draw(_world);
	if (Configuration::player->getKey()) 
	{
		window.draw(_objective2);
	}
	else
	{
		window.draw(_objective1);
	}
}

void SceneGame::initGUI()
{
	VLayout* layout = new VLayout();

	layout->setSpace(2);
	std::string findKeystring;
	findKeystring = "Find the Key to escape";

	Label* findKeytext = new Label(findKeystring);
	findKeytext->setCharacterSize(25);
	findKeytext->setTextColor(sf::Color(255, 255, 255));

	layout->add(findKeytext);

	
	_objective1.setLayout(layout);
	findKeytext->setPosition(20, 10);

	VLayout* layout2 = new VLayout();

	layout2->setSpace(2);
	std::string findDoorString;
	findDoorString = "Find the Door to escape";

	Label* findDoortext = new Label(findDoorString);
	findDoortext->setCharacterSize(25);
	findDoortext->setTextColor(sf::Color(255, 255, 255));

	layout2->add(findDoortext);

	_objective2.setLayout(layout2);
	findDoortext->setPosition(20, 10);
}
