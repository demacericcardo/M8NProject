#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "ECS.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Entities.hpp"
#include "Managers.hpp"

class RenderSystem : public System
{
private:
	TTF_Font* font = nullptr;
public:
	RenderSystem(Manager& manager);
	~RenderSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};