#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"


class RenderSystem : public System
{
public:
	RenderSystem(Manager& manager) : System(manager) {}
	~RenderSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		SDL_RenderClear(Game::renderer);
		for (auto& entity : entities)
		{
			if (entity->hasComponent<RenderComponent>() && entity->hasComponent<TransformComponent>())
			{
				SDL_Rect srcRect{}, destRect{};
				const RenderComponent& render = entity->getComponent<RenderComponent>();
				const TransformComponent& transform = entity->getComponent<TransformComponent>();

				srcRect.x = srcRect.y = 0;
				srcRect.w = transform.width;
				srcRect.h = transform.height;

				destRect.x = static_cast<int>(transform.position.x);
				destRect.y = static_cast<int>(transform.position.y);
				destRect.w = transform.width * transform.scale;
				destRect.h = transform.height * transform.scale;

				SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture(render.textureID), &srcRect, &destRect);
			}
		}
		SDL_RenderPresent(Game::renderer);
	}
};