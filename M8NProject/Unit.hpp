#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Unit : public Entity
{
public:
	float speed = 250.0f;
	float stopDistance = 10.0f;

	bool isSelected = false;

	std::unique_ptr<Vector2D> currentDestination = nullptr;

	TransformComponent* transform = nullptr;
	RenderComponent* sprite = nullptr;
	AnimationComponent* animation = nullptr;

	Unit(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>();
		sprite = &addComponent<RenderComponent>("bot");
		animation = &addComponent<AnimationComponent>("botIdle");
	}

	Unit(Manager& manager, float x, float y) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(x, y);
		sprite = &addComponent<RenderComponent>("bot");
		animation = &addComponent<AnimationComponent>("botIdle");
	}

	~Unit() {}
};
