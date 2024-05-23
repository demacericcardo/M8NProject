#pragma once

#include "ECS.hpp"

class StateAnimationSystem : public System
{
public:
	StateAnimationSystem(Manager& manager) : System(manager) {}
	~StateAnimationSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
	void setUnitAnimation(std::unique_ptr<Entity>& entity);
	void setPlayerAnimation(std::unique_ptr<Entity>& entity);
};