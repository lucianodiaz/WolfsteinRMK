#include "GUI/Button.h"

Button::FuncType Button::defaultFunc = [](const sf::Event&, Button&)->void {};
Button::Button(Widget* parent) : Widget(parent),onClick(defaultFunc),_status(Status::None)
{
}

Button::~Button()
{
}

bool Button::processEvent(const sf::Event& evt, const sf::Vector2f& parent_pos)
{
	bool res = false;
	if (evt.type == sf::Event::MouseButtonReleased)
	{
		const sf::Vector2f pos = _position + parent_pos;
		const sf::Vector2f size = getSize();
		sf::FloatRect rect;

		rect.left = pos.x;
		rect.top = pos.y;
		rect.width = size.x;
		rect.height = size.y;

		if (rect.contains(evt.mouseButton.x, evt.mouseButton.y))
		{
			onClick(evt, *this);
			res = true;
		}
	}
	else if (evt.type == sf::Event::MouseMoved)
	{
		const sf::Vector2f pos = _position + parent_pos;
		const sf::Vector2f size = getSize();
		sf::FloatRect rect;

		rect.left = pos.x;
		rect.top = pos.y;
		rect.width = size.x;
		rect.height = size.y;

		int old_status = _status;
		_status = Status::None;

		const sf::Vector2f mousePos(evt.mouseMove.x, evt.mouseMove.y);
		if (rect.contains(mousePos))
		{
			_status |= Status::Hover; // this is equal to say _status = _status | Status::Hover
		}

		if ((old_status & Status::Hover) && !(_status & Status::Hover))
		{
			onMouseLeft();
		}
		else if (!(old_status & Status::Hover) && (_status & Status::Hover))
		{
			onMouseEntered();
		}
	}
	return res;
}

void Button::onMouseEntered()
{
	
}

void Button::onMouseLeft()
{
}

