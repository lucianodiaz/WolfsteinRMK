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

	void setGridPosition(float x, float y);

	void setGridPosition(sf::Vector2f pos);

	const sf::Vector2f& getPosition()const;

	virtual bool isCollide(const Entity& other) const = 0;

	virtual void update(sf::Time deltaTime) = 0;

	virtual bool isAlive()const;

	virtual void onDestroy();

protected:

	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::Vector2f _position{0.0f,0.0f};

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	World& _world;

	bool _alive;
};

template<typename ...Args>
inline void Entity::setPosition(Args && ...args)
{
	_sprite.setPosition(std::forward<Args>(args)...);
}
