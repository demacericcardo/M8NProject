#pragma once

#include "Vector2D.h"
#include "ECS.h"

class InputComponent : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};