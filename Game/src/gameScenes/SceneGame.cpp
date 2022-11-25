#include "gameScenes/SceneGame.h"
#include "Configuration.h"

SceneGame::SceneGame(World& world, Window& window, SceneStateMachine& ssm) :
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
}

void SceneGame::onDeactivate()
{
}

void SceneGame::setSwitchToScene(unsigned int id)
{
}

void SceneGame::processInput()
{
}

void SceneGame::update(sf::Time deltaTime)
{
}

void SceneGame::draw(Window& window)
{
}
