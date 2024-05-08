#pragma once

#include "Vector2D.h"
#include "ECS.h"

class InputComponent : public Component
{
public:
	InputComponent() {}
	~InputComponent() {}

	void reset()
	{
		up = false;
		down = false;
		left = false;
		right = false;
	}

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};