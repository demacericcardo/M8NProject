#pragma once

#include <SDL.h>

#include "ECS.hpp"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	ColliderComponent(int x, int y, int width, int height, std::string tag)
	{
		collider.x = x;
		collider.y = y;
		collider.w = width;
		collider.h = height;
		this->tag = tag;
	}
	~ColliderComponent() {}

	bool collidesWith(const ColliderComponent& other) const
	{
		return SDL_HasIntersection(&collider, &other.collider);
	}
};