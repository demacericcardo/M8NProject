#pragma once

#include <SDL.h>

#include "ECS.hpp"
#include "Components.hpp"
#include "Game.hpp"

class Camera {
private:
	Vector2D position;
	TransformComponent* target;

	Camera() : target(nullptr) {}
public:
	static Camera& getInstance();

	void setTarget(TransformComponent& target);
	void update();

	Vector2D getPosition() const { return position; }
};