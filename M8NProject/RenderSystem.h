#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"
#include "Camera.h"

class RenderSystem : public System
{
public:
	RenderSystem(Manager& manager) : System(manager) {}
	~RenderSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		SDL_RenderClear(Game::renderer);
		Vector2D cameraPos = Camera::getInstance().getPosition();
		for (auto& entity : entities)
		{
			if (entity->hasComponent<RenderComponent>() && entity->hasComponent<TransformComponent>())
			{
				RenderComponent& render = entity->getComponent<RenderComponent>();
				const TransformComponent& transform = entity->getComponent<TransformComponent>();

				render.srcRect.x = render.srcRect.y = 0;
				render.srcRect.w = render.width;
				render.srcRect.h = render.height;

				if (entity->hasComponent<AnimationComponent>() && entity->hasComponent<StateComponent>())
				{
					AnimationComponent& animation = entity->getComponent<AnimationComponent>();
					const StateComponent& state = entity->getComponent<StateComponent>();

					switch (state.getState())
					{
					case State::IDLE:
						animation.index = 0;
						animation.frames = 2;
						break;
					case State::WALK:
						animation.index = 1;
						animation.frames = 5;
						break;
					default:
						break;
					}

					render.srcRect.y = animation.index * render.height;
					render.srcRect.x = render.srcRect.w * static_cast<int>((SDL_GetTicks() / animation.speed) % animation.frames);
				}

				render.destRect.x = static_cast<int>(transform.position.x - cameraPos.x);
				render.destRect.y = static_cast<int>(transform.position.y - cameraPos.y);
				render.destRect.w = render.width * render.scale;
				render.destRect.h = render.height * render.scale;

				Player* playerEntity = dynamic_cast<Player*>(entity.get());

				if (playerEntity)
				{
					if (playerEntity->showInteraction)
					{
						SDL_Rect destRect = { render.destRect.x, render.destRect.y - 32, 32, 32 };
						SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture("trigger"), nullptr, &destRect);
					}
				}

				SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture(render.textureID), &render.srcRect, &render.destRect);
			}
		}
		SDL_RenderPresent(Game::renderer);
	}
};