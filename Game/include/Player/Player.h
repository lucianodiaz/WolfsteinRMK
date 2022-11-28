#pragma once
#include "Input/ActionTarget.h"
#include "Entity.h"
class Player :
    public Entity,public ActionTarget<int>
{

public:
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(World& world);

    virtual bool isCollide(const Entity& other) const override;

    virtual void update(sf::Time deltaTime) override;

    void processEvents();

    virtual void onDestroy();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    
    //FPS
    const float cameraHeight = 0.66f;//Heigth of player camera(1.0 is ceiling, 0.0 is floor)

    sf::Vector2f _position{ 2.f, 2.f };//Coordinates in WorldMap
    sf::Vector2f _direction{ 0.0f,1.0f };//direction, relative to (0,0)
	sf::Vector2f _plane{ -0.66f, 0.0f };//2d raycaster version of the camera plane
                                       //must be perpendicular to rotation
    float _size_f = 0.375f;// dimensions of player collision box, in tiles
    float _moveSpeed{ 5.0f };
    float _rotationSpeed{ 3.0f };

    sf::Vector2f size{ _size_f, _size_f };

    sf::VertexArray lines;

    sf::Vector2f rotateVec(sf::Vector2f vec, float value)const;

    int _rotateDirection{};

    int _moveForward{};

    sf::RenderStates _state;
};

