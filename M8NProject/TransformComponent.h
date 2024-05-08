#pragma once
#include "Vector2D.h"
#include "ECS.h"

class TransformComponent : public Component
{
public:
	Vector2D position;

	Vector2D velocity;
	int speed = 3;

	int height = 32;
	int width = 32;
	int scale = 1;

	TransformComponent()
	{
		position.zero();
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int h, int w, int s)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = s;
	}
};