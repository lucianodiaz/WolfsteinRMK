#pragma once
#include <SFML/Graphics.hpp>

class World : public sf::Drawable
{
public:
	World(const World&) = delete;
	World& operator=(const World&) = delete;

	World(float x, float y);
	virtual ~World();

	int getX()const;
	int getY()const;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	const int _x;
	const int _y;
};

