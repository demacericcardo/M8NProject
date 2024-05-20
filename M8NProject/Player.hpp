#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Player : public Entity
{
public:
	float speed = 250.0f;
	int minerals = 0;

	TransformComponent* transform;
	RenderComponent* sprite;
	StateComponent* state;
	AnimationComponent* animation;
	ColliderComponent* collider;

	bool hasInteracted = false;
	Entity* interactableEntity = nullptr;

	Player(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(200.0f, 200.0f);
		sprite = &addComponent<RenderComponent>("playerTexture", 100);
		state = &addComponent<StateComponent>(PlayerState::IDLE);
		animation = &addComponent<AnimationComponent>("playerIdle");
		collider = &addComponent<ColliderComponent>(static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), sprite->width, sprite->height, "player");
	}
	~Player() {}
};
