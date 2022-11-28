#include "GUI/Widget.h"

Widget::Widget(Widget* parent) : _parent(parent)
{
}

Widget::~Widget()
{
}

void Widget::setPosition(const sf::Vector2f& pos)
{
    _position = pos;
}

void Widget::setPosition(float x, float y)
{
    _position.x = x + (_parent ? _parent->getPosition().x : 0);
    _position.y = y + (_parent ? _parent->getPosition().y : 0);
}

const sf::Vector2f& Widget::getPosition() const
{
    return _position;
}

bool Widget::processEvent(const sf::Event& evt, const sf::Vector2f& parent_pos)
{
    return false;
}

void Widget::processEvents(const sf::Vector2f& parent_pos)
{
}

void Widget::updateShape()
{
    if (_parent)
        _parent->updateShape();
}
