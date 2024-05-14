#include "Camera.hpp"

Camera& Camera::getInstance()
{
	static Camera instance;
	return instance;
}

void Camera::setTarget(TransformComponent& target)
{
	this->target = &target;
}

void Camera::update()
{
	Vector2D targetPos = target->position;
	targetPos.x -= static_cast<float>(Game::SCREEN_WIDTH) / 2.0f;
	targetPos.y -= static_cast<float>(Game::SCREEN_HEIGHT) / 2.0f;

	position = position.lerp(targetPos, 0.05f);
}