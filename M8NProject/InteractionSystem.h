#pragma once

#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"

class InteractionSystem : public System
{
public:
	InteractionSystem(Manager& manager) : System(manager) {}
	~InteractionSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		for (auto& entity : entities)
		{
		}
	}
};