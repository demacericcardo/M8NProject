#pragma once

#include "ECS.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Rock.hpp"

class InputSystem : public System
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool interact = false;
	bool mouseLeftClick = false;

	std::unique_ptr<Vector2D> mousePosClicked;

	InputSystem(Manager& manager) : System(manager) {}
	~InputSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
};