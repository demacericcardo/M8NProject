#pragma once
#include "Vector2D.h"
#include "ECS.h"

class TransformComponent : public Component
{
public:
	Vector2D position;

	Vector2D velocity;
	int speed = 3;

	TransformComponent()
	{
		position.zero();
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
};