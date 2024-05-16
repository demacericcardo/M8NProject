#pragma once

#include "StateAnimationSystem.hpp"
#include "Enums.hpp"
#include "Player.hpp"

void StateAnimationSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity : entities)
	{
		setPlayerAnimation(entity);
	}
}

void StateAnimationSystem::setPlayerAnimation(std::unique_ptr<Entity>& entity)
{
	Player* playerEntity = dynamic_cast<Player*>(entity.get());

	if (playerEntity)
	{
		switch (playerEntity->state->getState())
		{
		case PlayerState::IDLE:
			playerEntity->animation->setAnimation("playerIdle");
			break;
		case PlayerState::WALK:
			playerEntity->animation->setAnimation("playerWalk");
			break;
		default:
			break;
		}
	}
}
