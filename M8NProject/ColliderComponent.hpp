#pragma once

#include <SDL.h>

#include "ECS.hpp"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	ColliderComponent(int x, int y, int w, int h, std::string tag)
		: collider({ x, y, w, h }), tag(tag) {}

	~ColliderComponent() {}
};