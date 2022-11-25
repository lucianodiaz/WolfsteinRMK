#pragma once
#include "Window.h"

class Scene
{
public:
	virtual void onCreate() = 0;

	virtual void onDestroy() = 0;

	virtual void onActivate() {};

	virtual void onDeactivate() {};


	virtual void processInput() {};
	virtual void update(sf::Time deltaTime) {};
	virtual void draw(Window& window) {};
};