#pragma once

#include "BaseRenderSystem.hpp"
#include "Input.hpp"

BaseRenderSystem::BaseRenderSystem(Manager& manager) : RenderSystem(manager)
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

void BaseRenderSystem::render(std::vector<std::unique_ptr<Entity>>& entities)
{
	Vector2D cameraPos = Camera::getInstance().getPosition();

	std::sort(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& a, const std::unique_ptr<Entity>& b) {
		if (a->hasComponent<RenderComponent>() && b->hasComponent<RenderComponent>()) {
			return a->getComponent<RenderComponent>().zIndex < b->getComponent<RenderComponent>().zIndex;
		}
		return false;
		});

	for (auto& entity : entities)
	{
		if (entity->hasComponent<TransformComponent>() && entity->hasComponent<RenderComponent>())
		{
			RenderComponent& render = entity->getComponent<RenderComponent>();
			const TransformComponent& transform = entity->getComponent<TransformComponent>();

			Vector2D interpolatedPosition;
			if (transform.previousPosition) {
				interpolatedPosition = *transform.previousPosition + (transform.position - *transform.previousPosition) * Game::interpolation;
			}
			else {
				interpolatedPosition = transform.position;
			}

			float renderScale = render.scale * Camera::getInstance().getZoom();

			render.destRect.x = static_cast<int>(interpolatedPosition.x - cameraPos.x);
			render.destRect.y = static_cast<int>(interpolatedPosition.y - cameraPos.y);

			render.destRect.w = render.width * renderScale;
			render.destRect.h = render.height * renderScale;

			SDL_RendererFlip flip = render.isNotFlipped ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

			SDL_RenderCopyEx(Game::renderer, AssetManager::getInstance().getTexture(render.getTextureID()), &render.srcRect, &render.destRect, 0, NULL, flip);
		}

		renderColliders(entity, cameraPos);
		renderPlayerInterface(entity);
	}
}

void BaseRenderSystem::renderColliders(std::unique_ptr<Entity>& entity, Vector2D& cameraPos)
{
	if (entity->hasComponent<ColliderComponent>() && (entity->hasColliderComponent("notwalkable") || entity->hasColliderComponent("player")))
	{
		ColliderComponent& colliderComponent = entity->getComponent<ColliderComponent>();

		SDL_Rect rect{};

		rect.x = static_cast<int>((colliderComponent.collider.x - cameraPos.x));
		rect.y = static_cast<int>((colliderComponent.collider.y - cameraPos.y));
		rect.w = static_cast<int>(colliderComponent.collider.w);
		rect.h = static_cast<int>(colliderComponent.collider.h);

		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Game::renderer, &rect);
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	}
}   

void BaseRenderSystem::renderPlayerInterface(std::unique_ptr<Entity>& entity)
{
	Player* playerEntity = dynamic_cast<Player*>(entity.get());

	if (playerEntity)
	{
		SDL_Color color = { 0, 0, 0 };
		std::string stringMineralValue = std::to_string(playerEntity->minerals);
		stringMineralValue = "Minerals: " + stringMineralValue;

		SDL_Surface* surface = TTF_RenderText_Solid(font, stringMineralValue.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

		SDL_Rect textRect = { Game::SCREEN_WIDTH - surface->w - 10, 30, surface->w, surface->h };

		SDL_RenderCopy(Game::renderer, texture, NULL, &textRect);

		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);

		Input& input = Input::getInstance();

		if (input.mousePosClicked) {
			SDL_Rect destRect{};
			destRect.x = static_cast<int>(input.mousePosClicked->x);
			destRect.y = static_cast<int>(input.mousePosClicked->y);
			destRect.w = input.mouseXPos - static_cast<int>(input.mousePosClicked->x);
			destRect.h = input.mouseYPos - static_cast<int>(input.mousePosClicked->y);

			SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRect(Game::renderer, &destRect);
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		}
	}
}
