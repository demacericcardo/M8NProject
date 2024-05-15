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

		if (botEntity)
		{
			if (input.mousePosClicked && botEntity->hasComponent<TransformComponent>())
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

			if (input.mouseRightClick && botEntity->isSelected && botEntity->hasComponent<TransformComponent>())
			{
				const TransformComponent& transform = botEntity->getComponent<TransformComponent>();
				botEntity->currentDestination = { static_cast<float>(input.mouseXPos + cameraPos.x), static_cast<float>(input.mouseYPos + cameraPos.y) };
				botEntity->hasCommand = true;
			}

			if (botEntity->hasCommand && botEntity->hasComponent<TransformComponent>())
			{
				TransformComponent& transform = botEntity->getComponent<TransformComponent>();
				Vector2D direction = botEntity->currentDestination - transform.position;
				float distance = direction.magnitude();

				if (distance > botEntity->stopDistance)
				{
					direction = direction.normalize();
					transform.position += direction * (botEntity->speed);
				}
				else
				{
					botEntity->hasCommand = false;
				}
			}
		}
	}
}