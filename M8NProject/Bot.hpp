#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Bot : public Entity
{
public:
	float speed = 5.0f;
	float stopDistance = 10.0f;

	bool isSelected = false;

	std::unique_ptr<Vector2D> currentDestination = nullptr;

	TransformComponent* transform = nullptr;
	RenderComponent* sprite = nullptr;
	AnimationComponent* animation = nullptr;

	Bot(Manager& manager, TransformComponent* target) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>();
		sprite = &addComponent<RenderComponent>("bot");
		animation = &addComponent<AnimationComponent>("botIdle");
	}

	Bot(Manager& manager, TransformComponent* target, float x, float y) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(x, y);
		sprite = &addComponent<RenderComponent>("bot");
		animation = &addComponent<AnimationComponent>("botIdle");
	}

	~Bot() {}
};
