#include "Camera.hpp"

void Camera::setTarget(TransformComponent& target)
{
	this->target = &target;
}

void Camera::update()
{
    if (target) {
        Vector2D targetPos = target->position;
        targetPos.x -= static_cast<float>(Game::SCREEN_WIDTH) / 2.0f;
        targetPos.y -= static_cast<float>(Game::SCREEN_HEIGHT) / 2.0f;

        targetPos.x *= zoomFactor;
        targetPos.y *= zoomFactor;

        position = position.lerp(targetPos, cameraSpeed * Game::frameLength);
    }
}