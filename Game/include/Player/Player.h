#pragma once
#include "Input/ActionTarget.h"
#include "Entity.h"

class Camera2d;
class AnimationManager;



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

    void Shoot();

    void receiveDamage(float dmg);

    void getHealth(float heal);

    virtual void onDestroy();

    void setKey(bool key) { _key = key; };
    bool getKey()const { return _key; };
    
    enum class states
    {
        Idle,
        Pistol,
        MachineGun
    };
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    
    void startShooting();
    void stopShooting();
    std::unique_ptr<AnimationManager> _animationManager;
    std::unique_ptr<Camera2d> _camera;

    //FPS
    sf::Vector2f _position{ 0.0f, 0.0f };//Coordinates in WorldMap
    sf::Vector2f _direction{ 0.0f,1.0f };//direction, relative to (0,0)
	sf::Vector2f _plane{ -0.66f, 0.0f };//2d raycaster version of the camera plane
                                       //must be perpendicular to rotation
    float _size_f = 0.375f;// dimensions of player collision box, in tiles
    float _moveSpeed{ 5.0f };
    float _rotationSpeed{ 2.0f };

    sf::Vector2f size{ _size_f, _size_f };

    int _rotateDirection{};

    int _moveForward{};

    sf::Time _timeSinceLastShoot;

    float _health;

    bool _key{};

    bool _isShooting{};

    int _ammo;
};

