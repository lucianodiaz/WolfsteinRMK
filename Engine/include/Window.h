#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using std::string;

class Window
{
private:
	int _width;
	int _height;
	string _title;
	std::unique_ptr<sf::RenderWindow> _window;
public:
	Window(int width, int height, string title);

	virtual ~Window();
	sf::RenderWindow& getRenderWindow() { return *_window; }const
	bool isOpen() const { return _window->isOpen(); };
	bool pollEvent(sf::Event& evt);
	void clear();
	void draw(sf::Drawable& target,const sf::RenderStates& states =sf::RenderStates::Default);
	void display();
	void close();

	const sf::Vector2u& getWindowCentrePos()const { return sf::Vector2u(_window->getSize().x / 2, _window->getSize().y / 2); };
};

