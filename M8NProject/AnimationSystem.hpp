#pragma once

#include "ECS.hpp"

class AnimationSystem : public System
{
public:
	AnimationSystem(Manager& manager) : System(manager) {}
	~AnimationSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};
