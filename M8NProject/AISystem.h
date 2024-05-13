#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"
#include "Entities.h"

class AISystem : public System
{
public:
	AISystem(Manager& manager) : System(manager) {}
	~AISystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		for (auto& entity : entities)
		{
			if (entity->hasComponent<TransformComponent>() && entity->hasComponent<StateComponent>())
			{
				Bot* currentEntity = dynamic_cast<Bot*>(entity.get());

				if (currentEntity)
				{
					InputComponent& input = entity->getComponent<InputComponent>();
					TransformComponent& transform = entity->getComponent<TransformComponent>();
					StateComponent& state = entity->getComponent<StateComponent>();

					float dx = currentEntity->currentTarget->position.x - transform.position.x;
					float dy = currentEntity->currentTarget->position.y - transform.position.y;
					float distance = sqrt(dx * dx + dy * dy);

					if (distance > currentEntity->stopDistance)
					{
						transform.position.x = transform.position.x + dx * currentEntity->lerpSpeed;
						transform.position.y = transform.position.y + dy * currentEntity->lerpSpeed;
					}
				}
			}
		}
	}
};