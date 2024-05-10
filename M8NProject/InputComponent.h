#pragma once

#include "ECS.h"

class InputComponent : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool interact = false;

	InputComponent() {}
	~InputComponent() {}

	void reset()
	{
		up = false;
		down = false;
		left = false;
		right = false;
		interact = false;
	}
};