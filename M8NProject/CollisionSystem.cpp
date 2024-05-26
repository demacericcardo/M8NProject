#pragma once

#include "CollisionSystem.hpp"

void CollisionSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	float zoom = Camera::getInstance().getZoom();

	for (auto& entity1 : entities)
	{
		if (entity1->hasComponent<ColliderComponent>() && entity1->hasComponent<TransformComponent>())
		{
			TransformComponent& transform1 = entity1->getComponent<TransformComponent>();
			ColliderComponent& colliderComponent1 = entity1->getComponent<ColliderComponent>();

			colliderComponent1.collider.x = static_cast<int>(transform1.position.x);
			colliderComponent1.collider.y = static_cast<int>(transform1.position.y);

			float renderScale = colliderComponent1.scale * zoom;

			colliderComponent1.collider.w = colliderComponent1.width * renderScale;
			colliderComponent1.collider.h = colliderComponent1.height * renderScale;

			Player* playerEntity = dynamic_cast<Player*>(entity1.get());
			Unit* unitEntity = dynamic_cast<Unit*>(entity1.get());

			for (auto& entity2 : entities)
			{
				if (entity1 != entity2 && entity2->hasComponent<ColliderComponent>())
				{
					if (playerEntity)
						checkPlayerCollisions(entity2, colliderComponent1, playerEntity);

					if (unitEntity)
					{
						checkUnitsCollisions(entity2, unitEntity, entities, entity1);
					}
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

		if (!unitEntity->currentDestination && collidesWith(*unitEntity->collider, colliderAnotherUnit))
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

					if (!isDestinationSet && collidesWith(*unitEntity->collider, otherCollider))
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

void CollisionSystem::checkPlayerCollisions(std::unique_ptr<Entity>& entity2, ColliderComponent& collider1, Player* playerEntity)
{
	if (entity2->hasColliderComponent("notwalkable")) {
		ColliderComponent& colliderBlock = entity2->getColliderComponent("notwalkable");

		if (collidesWith(collider1, colliderBlock) && playerEntity->transform->previousPosition)
			playerEntity->transform->position = *playerEntity->transform->previousPosition;
	}

	if (entity2->hasColliderComponent("interactable"))
	{
		ColliderComponent& colliderInteractable = entity2->getColliderComponent("interactable");

		if (collidesWith(collider1, colliderInteractable))
			playerEntity->interactableEntity = entity2.get();
		else
			playerEntity->interactableEntity = nullptr;
	}
}

bool CollisionSystem::collidesWith(const ColliderComponent& first, const ColliderComponent& second)
{
	return SDL_HasIntersection(&first.collider, &second.collider);
}