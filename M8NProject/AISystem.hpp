#pragma once

#include "ECS.hpp"
#include "Entities.hpp"

class AISystem : public System
{
public:
	AISystem(Manager& manager) : System(manager) {}
	~AISystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};