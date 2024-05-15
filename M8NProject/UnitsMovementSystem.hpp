#pragma once

#include "ECS.hpp"

class UnitsMovementSystem : public System
{
public:
	UnitsMovementSystem(Manager& manager) : System(manager) {}
	~UnitsMovementSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};

