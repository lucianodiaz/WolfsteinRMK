#pragma once
#include <SFML/Graphics.hpp>
class Widget : public sf::Drawable
{
public:
	Widget(const Widget&) = delete;
	Widget& operator=(Widget&) = delete;

	Widget(Widget* parent = nullptr);
	virtual ~Widget();

	void setPosition(const sf::Vector2f& pos);
	void setPosition(float x, float y);

	const sf::Vector2f& getPosition()const;

	virtual sf::Vector2f getSize()const = 0;

protected:
	friend class Container;
	friend class VLayout;

	virtual bool processEvent(const sf::Event& evt, const sf::Vector2f& parent_pos);
	virtual void processEvents(const sf::Vector2f& parent_pos);

	virtual void updateShape();

	Widget* _parent;

	sf::Vector2f _position{};
};
