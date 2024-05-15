#pragma once

#include <SDL.h>

#include "ECS.hpp"
#include "Components.hpp"
#include "Game.hpp"

class Camera {
private:
	Vector2D position;
	TransformComponent* target;

	float cameraSpeed = 0.25f;

	Camera() : target(nullptr) {}
public:
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;

	static Camera& getInstance()
	{
		static Camera instance;
		return instance;
	}

	void setTarget(TransformComponent& target);
	void update();

	Vector2D getPosition() const { return position; }
};