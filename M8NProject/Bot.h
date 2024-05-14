#pragma once


#include "Entity.h"
#include "Components.h"

class Bot : public Entity
{
public:
	float speed = 0.025f;
	float stopDistance = 50.0f;

	bool isSelected = false;

	TransformComponent* currentTarget;
	TransformComponent* transform;
	RenderComponent* sprite;
	StateComponent* state;
	AnimationComponent* animation;

	Bot(Manager& manager, TransformComponent* target) : Entity(manager)
	{
		currentTarget = target;
		transform = &addComponent<TransformComponent>(200, 200);
		sprite = &addComponent<RenderComponent>("playerTexture");
		state = &addComponent<StateComponent>(State::IDLE);
		animation = &addComponent<AnimationComponent>(0, 2, 100);
	}
	~Bot() {}
};
