#pragma once
#include "World.h"

class Camera2d : public sf::Drawable, private sf::NonCopyable
{
public:
	Camera2d(World& _world, sf::Vector2f& _position, sf::Vector2f& _direction,sf::Vector2f size,sf::Vector2f& plane);
	void Raycasting(float rotation);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
protected:
	
	sf::Vector2f rotateVec(sf::Vector2f vec, float value)const;

	sf::Vector2f& _position;//Coordinates in WorldMap
	sf::Vector2f& _direction;//direction, relative to (0,0)
	sf::Vector2f& _plane;
	sf::Vector2f size;

	
	const float cameraHeight = 0.66f;//Heigth of player camera(1.0 is ceiling, 0.0 is floor)
	sf::VertexArray lines;
	sf::RenderStates _state;

	World& _world;
};
