#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "ECS.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "Entities.hpp"
#include "Managers.hpp"

class BaseRenderSystem : public RenderSystem
{
private:
	TTF_Font* font = nullptr;
public:
	BaseRenderSystem(Manager& manager);
	~BaseRenderSystem() {}

	void render(std::vector<std::unique_ptr<Entity>>& entities) override;
	void renderPlayerInterface(std::unique_ptr<Entity>& entity);
};