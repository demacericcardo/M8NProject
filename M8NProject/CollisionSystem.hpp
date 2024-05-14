#pragma once

#include "ECS.hpp"
#include "Entities.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem(Manager& manager) : System(manager) {}
	~CollisionSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};