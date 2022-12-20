#include "Actor.h"

Actor::Actor(Configuration::Textures texId, World& world) : Entity(texId , world)
{
    _spriteLines = sf::VertexArray(sf::Lines,_world.getWidth());
    _collide = false;
}

bool Actor::isCollide(const Entity& other) const
{
    return false;
}

void Actor::update(sf::Time deltaTime)
{
    /*_spriteLines.clear();
    _spriteLines.resize(0);*/
    //Entity::update(deltaTime);
    //_spriteLines.resize(0);
}

void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    target.draw(_spriteLines, &_texture);

}

sf::Texture Actor::getTexture() const
{
    return _texture;
}
