#pragma once

#include "MouseOverlaySystem.hpp"
#include "Input.hpp"
#include "Rock.hpp"

void MouseOverlaySystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Input& input = Input::getInstance();
	Vector2D cameraPos = Camera::getInstance().getPosition();

	for (auto& entity : entities)
	{
		if (entity->hasComponent<ColliderComponent>() && entity->hasColliderComponent("targetCollider"))
		{
			ColliderComponent& colliderComponent = entity->getColliderComponent("targetCollider");
			int worldMouseX = input.mouseXPos + static_cast<int>(cameraPos.x);
			int worldMouseY = input.mouseYPos + static_cast<int>(cameraPos.y);

			if (worldMouseX >= colliderComponent.collider.x && worldMouseX <= colliderComponent.collider.x + colliderComponent.collider.w &&
				worldMouseY >= colliderComponent.collider.y && worldMouseY <= colliderComponent.collider.y + colliderComponent.collider.h)
				input.entityMouseOverlaid = entity.get();
			else
				input.entityMouseOverlaid = nullptr;
		}
	}
}
