#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Components.h"
#include "Game.h"

class Camera {
private:
	Vector2D position;
	TransformComponent* target;

	Camera() : target(nullptr) {}
public:
	static Camera& getInstance()
	{
		static Camera instance;
		return instance;
	}

	void setTarget(TransformComponent& target)
	{
		this->target = &target;
	}

	void update()
	{
		Vector2D targetPos = target->position;
		targetPos.x -= static_cast<float>(Game::SCREEN_WIDTH) / 2;
		targetPos.y -= static_cast<float>(Game::SCREEN_HEIGHT) / 2;

		position = position.lerp(targetPos, 0.05f);
	}

	Vector2D getPosition() const { return position; }
};