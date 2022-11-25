#pragma once
#include <memory>
#include <unordered_map>
#include "Scene/Scene.h"
#include "Window.h"

class SceneStateMachine
{
public:
	SceneStateMachine();

	void processInput();
	void update(sf::Time deltaTime);
	void draw(Window& window);

	unsigned int add(std::shared_ptr<Scene> scene);

	void switchTo(unsigned int id);

	void remove(unsigned int id);

private:
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> _scenes;

	std::shared_ptr<Scene> _curScene;

	unsigned int _insertedSceneId{};
};