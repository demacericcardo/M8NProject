#pragma once

#include "Entity.h"
#include "Components.h"

class Player : public Entity
{
public:
	int minerals = 0;

	TransformComponent* transform;
	RenderComponent* sprite;
	InputComponent* input;
	StateComponent* state;
	AnimationComponent* animation;
	ColliderComponent* collider;

	bool hasInteracted = false;
	Entity* interactableEntity = nullptr;

	Player(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(200, 200);
		sprite = &addComponent<RenderComponent>("playerTexture", 100);
		input = &addComponent<InputComponent>();
		state = &addComponent<StateComponent>(State::IDLE);
		animation = &addComponent<AnimationComponent>(0, 2, 100);
		collider = &addComponent<ColliderComponent>(transform->position.x, transform->position.y, sprite->width, sprite->height, "player");
	}
	~Player() {}
};
