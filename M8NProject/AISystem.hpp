#pragma once

#include <SDL.h>

#include "ECS.hpp"
#include "Game.hpp"
#include "Components.hpp"
#include "Managers.hpp"
#include "Entities.hpp"

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
					/*playerEntity->input->mousePosClicked
					Game::mouseXPos;
					Game::mouseYPos;*/
				}
			}
		}
	}
};