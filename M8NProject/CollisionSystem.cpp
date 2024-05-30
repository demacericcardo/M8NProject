#pragma once

#include "CollisionSystem.hpp"

void CollisionSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	float zoom = Camera::getInstance().getZoom();

	for (auto& entity : entities)
	{
		if (entity->hasComponent<ColliderComponent>() && entity->hasComponent<TransformComponent>())
		{
			Player* playerEntity = dynamic_cast<Player*>(entity.get());
			Unit* unitEntity = dynamic_cast<Unit*>(entity.get());

			for (auto& collidedEntity : entities)
			{
				if (entity != collidedEntity && collidedEntity->hasComponent<ColliderComponent>())
				{
					if (playerEntity)
						checkPlayerCollisions(collidedEntity, playerEntity);

					if (unitEntity)
						checkUnitsCollisions(collidedEntity, unitEntity, entities, entity);
				}
			}
		}
	}
}

void CollisionSystem::checkUnitsCollisions(std::unique_ptr<Entity>& entity2, Unit* unitEntity, std::vector<std::unique_ptr<Entity>>& entities, std::unique_ptr<Entity>& entity1)
{
	if (entity2->hasColliderComponent("selectableUnit"))
	{
		ColliderComponent& colliderAnotherUnit = entity2->getColliderComponent("selectableUnit");

		if (!unitEntity->currentDestination && SDL_HasIntersection(&unitEntity->collider->collider, &colliderAnotherUnit.collider))
		{
			unitEntity->isOverlapped = true;
			Vector2D direction = unitEntity->transform->position - entity2->getComponent<TransformComponent>().position;
			direction.normalize();
			unitEntity->transform->velocity = direction * unitEntity->transform->speed;
		}
		else if (unitEntity->isOverlapped)
		{
			bool isColliding = false;
			for (auto& otherEntity : entities)
			{
				if (otherEntity != entity1 && otherEntity->hasColliderComponent("selectableUnit"))
				{
					ColliderComponent& otherCollider = otherEntity->getColliderComponent("selectableUnit");
					bool isDestinationSet = std::any_of(entities.begin(), entities.end(), [](const std::unique_ptr<Entity>& entity) {
						Unit* unitEntity = dynamic_cast<Unit*>(entity.get());
						return unitEntity && unitEntity->currentDestination;
						});

					if (!isDestinationSet && SDL_HasIntersection(&unitEntity->collider->collider, &otherCollider.collider))
					{
						isColliding = true;
						break;
					}
				}
			}

			if (!isColliding)
			{
				unitEntity->isOverlapped = false;
				unitEntity->transform->velocity = Vector2D(0, 0);
			}
		}
	}
}

void CollisionSystem::checkPlayerCollisions(std::unique_ptr<Entity>& entity2, Player* playerEntity)
{
	ColliderComponent& playerCollider = playerEntity->getColliderComponent("player");

	if (entity2->hasColliderComponent("notwalkable")) {
		ColliderComponent& blockCollider = entity2->getColliderComponent("notwalkable");

		if (SDL_HasIntersection(&playerCollider.collider, &blockCollider.collider) && playerEntity->transform->previousPosition)
			playerEntity->transform->position = *playerEntity->transform->previousPosition;
	}

	if (entity2->hasColliderComponent("interactable"))
	{
		ColliderComponent& colliderInteractable = entity2->getColliderComponent("interactable");

		if (SDL_HasIntersection(&playerCollider.collider, &colliderInteractable.collider))
			playerEntity->interactableEntity = entity2.get();
		else
			playerEntity->interactableEntity = nullptr;
	}
}