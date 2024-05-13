#pragma once

#include "Entity.h"
#include "Components.h"

class Rock : public Entity
{
private:
	int interactableRange = 64;
	int minerals = 10;
public:
	Rock(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(100, 100);
		sprite = &addComponent<RenderComponent>("rockTexture");
		colliderBlock = &addComponent<ColliderComponent>(transform->position.x, transform->position.y, sprite->width, sprite->height, "notwalkable");
		collider = &addComponent<ColliderComponent>
			(
				transform->position.x - interactableRange / static_cast<float>(2),
				transform->position.y - interactableRange / static_cast<float>(2),
				sprite->width + interactableRange,
				sprite->height + interactableRange,
				"interactable"
			);
	}
	~Rock() {}

	void takeMineral() {
		minerals--;
		if (minerals <= 0) {
			destroy();
		}
	}

	TransformComponent* transform;
	RenderComponent* sprite;
	ColliderComponent* colliderBlock;
	ColliderComponent* collider;
};
