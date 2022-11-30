#pragma once
#include "Entity.h"

class StaticObject : public Entity, sf::NonCopyable
{
public:

	StaticObject(Configuration::Textures tex_id, World& world);

};

