#pragma once

#include "AISystem.hpp"

void AISystem::update(std::vector<std::unique_ptr<Entity>>& entities)
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