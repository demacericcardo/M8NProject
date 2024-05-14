#pragma once
#include "Vector2D.hpp"
#include "ECS.hpp"

class TransformComponent : public Component
{
public:
	Vector2D previousPosition;
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