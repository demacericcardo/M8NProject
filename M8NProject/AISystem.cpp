#pragma once

#include "AISystem.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Game.hpp"

void AISystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Input& input = Input::getInstance();
	Vector2D cameraPos = Camera::getInstance().getPosition();

	for (auto& entity : entities)
	{
		Bot* botEntity = dynamic_cast<Bot*>(entity.get());

		if (botEntity && botEntity->hasComponent<TransformComponent>())
		{
			TransformComponent& transformComponent = botEntity->getComponent<TransformComponent>();

			if (input.mousePosClicked)
			{
				const TransformComponent& transform = botEntity->getComponent<TransformComponent>();
				SDL_Point botPosition = { static_cast<int>(transform.position.x - cameraPos.x), static_cast<int>(transform.position.y - cameraPos.y) };

				int minX = std::min(input.mouseXPos, static_cast<int>(input.mousePosClicked->x));
				int minY = std::min(input.mouseYPos, static_cast<int>(input.mousePosClicked->y));
				int maxX = std::max(input.mouseXPos, static_cast<int>(input.mousePosClicked->x));
				int maxY = std::max(input.mouseYPos, static_cast<int>(input.mousePosClicked->y));

				SDL_Rect rect = { minX, minY, maxX - minX, maxY - minY };

				if (SDL_PointInRect(&botPosition, &rect))
					botEntity->isSelected = true;
				else
					botEntity->isSelected = false;
			}

			if (botEntity->isSelected)
				botEntity->sprite->setTextureId("botSelected");
			else
				botEntity->sprite->setTextureId("bot");

			if (input.mouseRightClick && botEntity->isSelected)
			{
				ParticleEmitter::getInstance().emitParticle("walkParticle", { static_cast<float>(input.mouseXPos) + cameraPos.x, static_cast<float>(input.mouseYPos) + cameraPos.y }, Vector2D(0, 0), 0.025f);

				if (botEntity->currentDestination)
				{
					botEntity->currentDestination->x = static_cast<float>(input.mouseXPos + cameraPos.x);
					botEntity->currentDestination->y = static_cast<float>(input.mouseYPos + cameraPos.y);
				}
				else
				{
					botEntity->currentDestination = std::make_unique<Vector2D>(static_cast<float>(input.mouseXPos + cameraPos.x), static_cast<float>(input.mouseYPos + cameraPos.y));
				}
			}

			if (botEntity->currentDestination)
			{
				Vector2D direction = *botEntity->currentDestination - transformComponent.position;
				float distance = direction.magnitude();

				if (distance > botEntity->stopDistance)
				{
					direction = direction.normalize();
					transformComponent.position += Vector2D(static_cast<int>(direction.x * botEntity->speed), static_cast<int>(direction.y * botEntity->speed));
				}
				else
				{
					botEntity->currentDestination.reset();
				}
			}
		}
	}
}