#pragma once

#include "StateAnimationSystem.hpp"
#include "Enums.hpp"
#include "Entities.hpp"

void StateAnimationSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity : entities)
	{
		setPlayerAnimation(entity);
		setUnitAnimation(entity);
	}
}

void StateAnimationSystem::setUnitAnimation(std::unique_ptr<Entity>& entity)
{
	Unit* unitEntity = dynamic_cast<Unit*>(entity.get());

	if (unitEntity)
	{
		if (unitEntity->state->hasStateChanged())
			unitEntity->animation->frameCounter = 0;

		switch (unitEntity->state->getState())
		{
		case UnitState::IDLE:
			unitEntity->animation->setAnimation("unitIdle");
			break;
		case UnitState::WALK:
			unitEntity->animation->setAnimation("unitWalk");
			break;
		default:
			break;
		}
	}
}

void StateAnimationSystem::setPlayerAnimation(std::unique_ptr<Entity>& entity)
{
	Player* playerEntity = dynamic_cast<Player*>(entity.get());

	if (playerEntity)
	{
		if (playerEntity->state->hasStateChanged())
			playerEntity->animation->frameCounter = 0;

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
