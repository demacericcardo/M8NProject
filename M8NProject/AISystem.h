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
				Bot* botEntity = dynamic_cast<Bot*>(entity.get());

				if (botEntity)
				{
				}

				Player* playerEntity = dynamic_cast<Player*>(entity.get());

				if (playerEntity)
				{
					playerEntity->input->mousePosClicked
					Game::mouseXPos;
					Game::mouseYPos;
				}
			}
		}
	}
};