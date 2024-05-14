#pragma once

#include "Entity.hpp"
#include "Components.hpp"

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
		transform = &addComponent<TransformComponent>(200.0f, 200.0f);
		sprite = &addComponent<RenderComponent>("playerTexture", 100);
		input = &addComponent<InputComponent>();
		state = &addComponent<StateComponent>(State::IDLE);
		animation = &addComponent<AnimationComponent>(0, 2, 100);
		collider = &addComponent<ColliderComponent>(static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), sprite->width, sprite->height, "player");
	}
	~Player() {}
};
