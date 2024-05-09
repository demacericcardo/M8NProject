#pragma once

#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"

class CollisionSystem : public System
{
public:
	CollisionSystem(Manager& manager) : System(manager) {}
	~CollisionSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		for (auto& entity1 : entities)
		{
			if (entity1->hasComponent<ColliderComponent>() && entity1->hasComponent<TransformComponent>())
			{
				TransformComponent& transform1 = entity1->getComponent<TransformComponent>();
				ColliderComponent& playerCollider = entity1->getColliderComponent("player");

				Vector2D previousPosition = transform1.position;

				playerCollider.collider.x = static_cast<int>(transform1.position.x);
				playerCollider.collider.y = static_cast<int>(transform1.position.y);

				for (auto& entity2 : entities)
				{
					if (entity1 != entity2 && entity2->hasComponent<ColliderComponent>())
					{
						ColliderComponent& colliderBlock = entity2->getColliderComponent("notwalkable");
						ColliderComponent& colliderInteractable = entity2->getColliderComponent("interactable");
						auto& transform2 = entity2->getComponent<TransformComponent>();

						if (playerCollider.tag == "player")
						{
							Player* playerEntity = dynamic_cast<Player*>(entity1.get());

							if (playerCollider.collidesWith(colliderBlock))
								playerEntity->transform->position = playerEntity->transform->previousPosition;

							if (playerCollider.collidesWith(colliderInteractable))
								playerEntity->showInteraction = true;
							else
								playerEntity->showInteraction = false;
						}
					}
				}
			}
		}
	}
};