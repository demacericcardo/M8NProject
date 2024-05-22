#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Unit : public Entity
{
public:
	float speed = 250.0f;

	bool isSelected = false;
	bool isOverlapped = false;

	std::optional<Vector2D> currentDestination;

	TransformComponent* transform = nullptr;
	RenderComponent* sprite = nullptr;
	AnimationComponent* animation = nullptr;
	ColliderComponent* collider = nullptr;

	Unit(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>();
		sprite = &addComponent<RenderComponent>("bot");
		animation = &addComponent<AnimationComponent>("botIdle");
		collider = &addComponent<ColliderComponent>("selectableUnit");
	}

	Unit(Manager& manager, float x, float y) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(x, y);
		sprite = &addComponent<RenderComponent>("bot");
		animation = &addComponent<AnimationComponent>("botIdle");
		collider = &addComponent<ColliderComponent>("selectableUnit");
	}

	~Unit() {}
};
