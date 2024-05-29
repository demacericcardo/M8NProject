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
		Unit* unitEntity = dynamic_cast<Unit*>(entity.get());

		if (unitEntity && unitEntity->hasComponent<TransformComponent>())
		{
			TransformComponent& transformComponent = unitEntity->getComponent<TransformComponent>();

			if (input.mousePosClicked)
			{
				const TransformComponent& transform = unitEntity->getComponent<TransformComponent>();
				SDL_Point botPosition = { static_cast<int>(transform.position.x - cameraPos.x), static_cast<int>(transform.position.y - cameraPos.y) };

				int minX = std::min(input.mouseXPos, static_cast<int>(input.mousePosClicked->x));
				int minY = std::min(input.mouseYPos, static_cast<int>(input.mousePosClicked->y));
				int maxX = std::max(input.mouseXPos, static_cast<int>(input.mousePosClicked->x));
				int maxY = std::max(input.mouseYPos, static_cast<int>(input.mousePosClicked->y));

				SDL_Rect rect = { minX, minY, maxX - minX, maxY - minY };

				SDL_Rect unitCollider = unitEntity->collider->collider;
				unitCollider.x -= static_cast<int>(cameraPos.x);
				unitCollider.y -= static_cast<int>(cameraPos.y);

				if (SDL_HasIntersection(&rect, &unitCollider))
					unitEntity->isSelected = true;
				else
					unitEntity->isSelected = false;
			}

			if (unitEntity->isSelected)
				unitEntity->sprite->setTextureId("botSelected");
			else
				unitEntity->sprite->setTextureId("bot");

			if (input.mouseRightClick && unitEntity->isSelected)
			{
				float locationX = static_cast<float>(input.mouseXPos - Game::CURSOR_WIDTH / 2) + cameraPos.x;
				float locationY = static_cast<float>(input.mouseYPos - Game::CURSOR_HEIGHT / 2) + cameraPos.y;

				ParticleEmitter::getInstance().emitParticle("selectionParticle", { locationX, locationY }, Vector2D(0, 0), 2.0f);

				unitEntity->currentDestination = { locationX, locationY };
			}

			if (unitEntity->currentDestination)
			{
				Vector2D direction = *unitEntity->currentDestination - transformComponent.position;
				float distance = direction.magnitude();

				if (distance > 5.0f)
				{
					direction = direction.normalize();
					transformComponent.position += Vector2D(direction.x * unitEntity->speed * Game::frameLength, direction.y * unitEntity->speed * Game::frameLength);
					unitEntity->state->setState(UnitState::WALK);
				}
				else
				{
					unitEntity->currentDestination.reset();
					unitEntity->state->setState(UnitState::IDLE);
				}
			}
		}
	}
}