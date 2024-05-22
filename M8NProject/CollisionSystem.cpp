#pragma once

#include "CollisionSystem.hpp"

void CollisionSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity1 : entities)
	{
		if (entity1->hasComponent<ColliderComponent>() && entity1->hasComponent<TransformComponent>())
		{
			TransformComponent& transform1 = entity1->getComponent<TransformComponent>();
			ColliderComponent& collider1 = entity1->getComponent<ColliderComponent>();

			collider1.collider.x = static_cast<int>(transform1.position.x);
			collider1.collider.y = static_cast<int>(transform1.position.y);

			for (auto& entity2 : entities)
			{
				if (entity1 != entity2 && entity2->hasComponent<ColliderComponent>())
				{
					Player* playerEntity = dynamic_cast<Player*>(entity1.get());

					if (playerEntity)
						checkPlayerCollision(entity2, collider1, playerEntity);

					Unit* unitEntity = dynamic_cast<Unit*>(entity1.get());

					if (unitEntity)
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
								// Check if the unitEntity is colliding with any other entity
								bool isColliding = false;
								for (auto& otherEntity : entities)
								{
									if (otherEntity != entity1 && otherEntity->hasColliderComponent("selectableUnit"))
									{
										ColliderComponent& otherCollider = otherEntity->getColliderComponent("selectableUnit");
										if (collidesWith(*unitEntity->collider, otherCollider))
										{
											isColliding = true;
											break;
										}
									}
								}

								// Only reset the isOverlapped flag and velocity if the unitEntity is not colliding with any other entity
								if (!isColliding)
								{
									unitEntity->isOverlapped = false;
									unitEntity->transform->velocity = Vector2D(0, 0);
								}
							}
						}
					}
				}
			}
		}
	}
}

void CollisionSystem::checkPlayerCollision(std::unique_ptr<Entity>& entity2, ColliderComponent& collider1, Player* playerEntity)
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