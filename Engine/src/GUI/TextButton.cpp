#include "GUI/TextButton.h"

TextButton::TextButton(const std::string& text, Widget* parent) : Button(parent), _label(text,this)
{
	setFillColor(sf::Color(86, 20, 19));
	setOutlineThickness(5);
	setOutlineColor(sf::Color(146, 20, 19));
}

TextButton::~TextButton()
{
}

void TextButton::setText(const std::string& text)
{
	_label.setText(text);
}

void TextButton::setCharacterSize(unsigned int size)
{
	_label.setCharacterSize(size);
}

void TextButton::setTextColor(const sf::Color& color)
{
	_txtColor = color;
	_label.setTextColor(color);
}

void TextButton::hideShape()
{
	_hideShape = !_hideShape;
	_shape.setFillColor(sf::Color(0, 0, 0, 0));
	_shape.setOutlineColor(sf::Color(0, 0, 0, 0));
}

void TextButton::setFillColor(const sf::Color& color)
{
	_fillColor = color;
	_shape.setFillColor(_fillColor);
}

void TextButton::setOutlineColor(const sf::Color& color)
{
	_outlineColor = color;
	_shape.setOutlineColor(_outlineColor);
}

void TextButton::setOutlineThickness(float thickness)
{
	_shape.setOutlineThickness(thickness);
}

sf::Vector2f TextButton::getSize() const
{
	sf::FloatRect rect = _shape.getGlobalBounds();
	return sf::Vector2f(rect.width, rect.height);
}

void TextButton::updateShape()
{
	sf::Vector2f labelSize = _label.getSize();
	unsigned int charSize = _label.getCharacterSize();

	_shape.setSize(sf::Vector2f(charSize * 2 + labelSize.x, charSize * 2 + labelSize.y));
	_label.setPosition(charSize, charSize);

	Widget::updateShape();
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.translate(_position);
	target.draw(_shape, states);
	target.draw(_label, states);
}

void TextButton::onMouseEntered()
{
	const float light = 1.4;

	if (!_hideShape)
	{
		_shape.setOutlineColor(sf::Color(_outlineColor.r * light,
			_outlineColor.g * light,
			_outlineColor.b * light));
		_shape.setFillColor(sf::Color(_fillColor.r * light,
			_fillColor.b * light,
			_fillColor.b * light));
	}
	else
	{
		_label.setTextColor(sf::Color(_txtColor.r * light,
			_txtColor.b * light,
			_txtColor.b * light));
	}
	

	
}

void TextButton::onMouseLeft()
{
	if (!_hideShape)
	{
		_shape.setOutlineColor(_outlineColor);
		_shape.setFillColor(_fillColor);
	}
	else
	{
		_label.setTextColor(_txtColor);
	}
}
