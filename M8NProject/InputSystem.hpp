#pragma once

#include "ECS.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Rock.hpp"

class InputSystem : public System
{
public:
	InputSystem(Manager& manager) : System(manager) {}
	~InputSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};