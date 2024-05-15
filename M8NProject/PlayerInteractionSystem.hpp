#pragma once

#include "ECS.hpp"

class PlayerInteractionSystem: public System
{
public:
	PlayerInteractionSystem(Manager& manager) : System(manager) {}
	~PlayerInteractionSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};

