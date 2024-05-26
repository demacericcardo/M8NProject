#pragma once

#include <SDL.h>

#include "ECS.hpp"

class ColliderComponent : public Component
{
public:
	std::string tag;

	SDL_Rect collider = { 0, 0, 0, 0 };

	int width = 32;
	int height = 32;
	int scale = 1;

	ColliderComponent(std::string tag)
		: tag(tag) {}

	ColliderComponent(TransformComponent* transform, int w, int h, std::string tag) : tag(tag)
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = w;
		collider.h = h;
		width = w;
		height = h;
	}


	~ColliderComponent() {}
};