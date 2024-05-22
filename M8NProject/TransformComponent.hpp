#pragma once
#include "Vector2D.hpp"
#include "ECS.hpp"
#include <optional>

class TransformComponent : public Component
{
public:
	std::optional<Vector2D> previousPosition;
	Vector2D position;

	Vector2D velocity;
	int speed = 500;

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