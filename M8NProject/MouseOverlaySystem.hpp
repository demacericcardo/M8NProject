#pragma once

#include "ECS.hpp"

class MouseOverlaySystem : public System
{
public:
	MouseOverlaySystem(Manager& manager) : System(manager) {}
	~MouseOverlaySystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};