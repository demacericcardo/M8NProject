#pragma once


#include "Entity.hpp"
#include "Components.hpp"

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
		transform = &addComponent<TransformComponent>(150.0f, 350.0f);
		sprite = &addComponent<RenderComponent>("bot");
		state = &addComponent<StateComponent>(State::IDLE);
		//animation = &addComponent<AnimationComponent>(0, 1, 100);
	}

	Bot(Manager& manager, TransformComponent* target, float x, float y) : Entity(manager)
	{
		currentTarget = target;
		transform = &addComponent<TransformComponent>(x, y);
		sprite = &addComponent<RenderComponent>("bot");
		state = &addComponent<StateComponent>(State::IDLE);
		//animation = &addComponent<AnimationComponent>(0, 1, 100);
	}

	~Bot() {}
};
