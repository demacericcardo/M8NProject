#pragma once

#include "ECS.hpp"
#include "Rock.hpp"

class PlayerMovementSystem : public System
{
public:
	PlayerMovementSystem(Manager& manager) : System(manager) {}
	~PlayerMovementSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};

