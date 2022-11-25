#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "World.h"
#include <Scene/SceneStateMachine.h>

class Window;

class Game
{
public:
	//Non copyable or assignable
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Game(int x=1280,int y=720);

	virtual ~Game();
	//Run with fixed time steps
	void run(int frame_per_seconds = 30);

	void update(sf::Time deltaTime);

	void draw();

	void processEvents();
private:

	std::unique_ptr<Window> _window;

	SceneStateMachine sceneStateMachine;
	World _world;
};

