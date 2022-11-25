#include "Window.h"

Window::Window(int width, int height, string title)
{
	_width = width;
	_height = height;
	_title = title;
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
}

Window::~Window()
{
	std::cout << "OnDestroy Winodw" << std::endl;
	//delete _window;
}

bool Window::pollEvent(sf::Event& evt)
{
	return _window->pollEvent(evt);
}

void Window::clear()
{
	_window->clear();
}

void Window::draw(sf::Drawable& target,const sf::RenderStates& states)
{
	_window->draw(target,states);
}

void Window::display()
{
	_window->display();
}

void Window::close()
{
	_window->close();
}
