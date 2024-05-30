#pragma once

#include "ECS.hpp"
#include "Entities.hpp"

class ColliderLocationSystem : public System
{
public:
	ColliderLocationSystem(Manager& manager) : System(manager) {}
	~ColliderLocationSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};