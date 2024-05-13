#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"
#include "Camera.h"

class RenderSystem : public System
{
public:
	TTF_Font* font = nullptr;

	RenderSystem(Manager& manager) : System(manager)
	{
		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(2);
		}

		font = TTF_OpenFont("assets/default.ttf", 24);
		if (font == NULL) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
		}
	}
	~RenderSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		SDL_RenderClear(Game::renderer);
		Vector2D cameraPos = Camera::getInstance().getPosition();
		
		std::sort(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) {
			if (a->hasComponent<RenderComponent>() && b->hasComponent<RenderComponent>()) {
				return a->getComponent<RenderComponent>().zIndex < b->getComponent<RenderComponent>().zIndex;
			}
			return false;
			});

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
					if (playerEntity->interactableEntity)
					{
						SDL_Rect destRect = { render.destRect.x, render.destRect.y - 48, 32, 32 };
						SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture("trigger"), nullptr, &destRect);
					}

					SDL_Color color = { 0, 0, 0 };
					std::string stringMineralValue = std::to_string(playerEntity->minerals);
					stringMineralValue = "Minerals: " + stringMineralValue;

					SDL_Surface* surface = TTF_RenderText_Solid(font, stringMineralValue.c_str(), color);
					SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

					SDL_Rect textRect = { Game::SCREEN_WIDTH - surface->w - 10, 30, surface->w, surface->h };

					SDL_RenderCopy(Game::renderer, texture, NULL, &textRect);

					SDL_FreeSurface(surface);
					SDL_DestroyTexture(texture);
				}


				Bot* botEntity = dynamic_cast<Bot*>(entity.get());

				if (botEntity)
				{
					TransformComponent& transform1 = botEntity->getComponent<TransformComponent>();
					TransformComponent* transform2 = botEntity->currentTarget;

					// Subtract the camera's position from the entity's position
					int x1 = static_cast<int>(transform1.position.x + 16 - cameraPos.x);
					int y1 = static_cast<int>(transform1.position.y + 16 - cameraPos.y);
					int x2 = static_cast<int>(transform2->position.x + 16 - cameraPos.x);
					int y2 = static_cast<int>(transform2->position.y + 16 - cameraPos.y);

					SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawLine(Game::renderer, x1, y1, x2, y2);
					SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				}

				SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture(render.getTextureID()), &render.srcRect, &render.destRect);
			}
		}
		SDL_RenderPresent(Game::renderer);
	}
};