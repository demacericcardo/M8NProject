#pragma once

#include "ECS.h"
#include "RenderComponent.h"

class RenderSystem : public System
{
public:
	void update(std::vector<std::unique_ptr<Entity>> entities) override
	{
		for (auto& entity : entities)
		{
			if (entity->hasComponent<RenderComponent>())
			{

			}
		}
	}
};