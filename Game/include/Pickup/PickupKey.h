#pragma once
#include "Actor.h"
class PickupKey :
    public Actor
{
public:
    PickupKey(Configuration::Textures tex_id, World& world);

    virtual bool isCollide(const Entity& other) const override;

    virtual void update(sf::Time deltaTime) override;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

