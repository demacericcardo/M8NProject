#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Rock : public Entity
{
private:
	int interactableRange = 64;
	int minerals = 10;
public:
	Rock(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(100.0f, 100.0f);
		sprite = &addComponent<RenderComponent>("rockTexture");
		colliderBlock = &addComponent<ColliderComponent>(static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), sprite->width, sprite->height, "notwalkable");
		collider = &addComponent<ColliderComponent>
			(
				static_cast<int>(transform->position.x) - interactableRange / 2,
				static_cast<int>(transform->position.y) - interactableRange / 2,
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
