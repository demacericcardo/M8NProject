#pragma once

#include "ColliderLocationSystem.hpp"

void ColliderLocationSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	float zoom = Camera::getInstance().getZoom();

	for (auto& entity : entities)
	{
		if (entity->hasComponent<ColliderComponent>() && entity->hasComponent<TransformComponent>())
		{
			TransformComponent& transform = entity->getComponent<TransformComponent>();
			std::vector<ColliderComponent*> colliderComponents = entity->getComponents<ColliderComponent>();

			for (ColliderComponent* colliderComponent : colliderComponents)
			{
				colliderComponent->collider.x = static_cast<int>(transform.position.x);
				colliderComponent->collider.y = static_cast<int>(transform.position.y);

				float renderScale = colliderComponent->scale * zoom;

				colliderComponent->collider.w = colliderComponent->width * renderScale;
				colliderComponent->collider.h = colliderComponent->height * renderScale;
			}
		}
	}
}