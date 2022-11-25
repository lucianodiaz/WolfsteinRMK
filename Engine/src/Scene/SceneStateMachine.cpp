#include "Scene/SceneStateMachine.h"

SceneStateMachine::SceneStateMachine() : _scenes(0),_curScene(0)
{
}

void SceneStateMachine::processInput()
{
	if (_curScene)
	{
		_curScene->processInput();
	}
}

void SceneStateMachine::update(sf::Time deltaTime)
{
	if (_curScene)
	{
		_curScene->update(deltaTime);
	}
}

void SceneStateMachine::draw(Window& window)
{
	if (_curScene)
	{
		_curScene->draw(window);
	}
}

unsigned int SceneStateMachine::add(std::shared_ptr<Scene> scene)
{
	auto inserted = _scenes.insert(std::make_pair(_insertedSceneId, scene));
	_insertedSceneId++;
	inserted.first->second->onCreate();
	return _insertedSceneId-1;
}

void SceneStateMachine::switchTo(unsigned int id)
{
	auto it = _scenes.find(id);

	if (it != _scenes.end())
	{
		if (_curScene)
		{
			_curScene->onDeactivate();
		}

		_curScene = it->second;

		_curScene->onActivate();
	}
}

void SceneStateMachine::remove(unsigned int id)
{
	auto it = _scenes.find(id);

	if (it != _scenes.end())
	{
		if (_curScene == it->second)
		{
			_curScene = nullptr;
		}

		it->second->onDestroy();

		_scenes.erase(it);
	}
}
