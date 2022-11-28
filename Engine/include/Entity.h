#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include "Configuration.h"
#include "World.h"

class Entity : public sf::Drawable
{
public:

	//Non copyable or assignable
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	Entity(Configuration::Textures tex_id, World& world);
	virtual ~Entity();

	template<typename ... Args>
	void setPosition(Args&& ... args);

	const sf::Vector2f& getPosition()const;

	virtual bool isCollide(const Entity& other) const = 0;

	virtual void update(sf::Time deltaTime) = 0;

	virtual bool isAlive()const;

	virtual void onDestroy();

protected:
	sf::Sprite _sprite;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	World& _world;

	bool _alive;
};

template<typename ...Args>
inline void Entity::setPosition(Args && ...args)
{
	_sprite.setPosition(std::forward<Args>(args)...);
}
