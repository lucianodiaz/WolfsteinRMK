#pragma once
#include "Actor.h"

class World;


class Camera2d : public sf::Drawable, private sf::NonCopyable
{
public:
	Camera2d(World& _world, sf::Vector2f& _position, sf::Vector2f& _direction,sf::Vector2f size,sf::Vector2f& plane);
	void Raycasting(float rotation);
	void RaycastinWalls();
	void RaycastingSprite();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void restart();
protected:
	
	//1D Zbuffer
	std::vector<double> _ZBuffer;

	//arrays used to sort sprotes
	std::vector<int> _spriteOrder;
	std::vector<double> _spriteDistance;

	void sortSprites(std::vector<int>* order, std::vector<double>* dist, int amount);

	sf::Vector2f rotateVec(sf::Vector2f vec, float value)const;

	sf::Vector2f& _position;//Coordinates in WorldMap
	sf::Vector2f& _direction;//direction, relative to (0,0)
	sf::Vector2f& _plane;
	sf::Vector2f size;

	
	const float cameraHeight = 0.66f;//Heigth of player camera(1.0 is ceiling, 0.0 is floor)
	sf::VertexArray _lines;
	/*sf::VertexArray _spriteLines;*/
	sf::RenderStates _state;

	World& _world;
};

