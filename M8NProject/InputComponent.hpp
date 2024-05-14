#pragma once

#include "ECS.hpp"

class InputComponent : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool interact = false;
	bool mouseLeftClick = false;

	std::unique_ptr<Vector2D> mousePosClicked;

	InputComponent() {}
	~InputComponent() {}
};