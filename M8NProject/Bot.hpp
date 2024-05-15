#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Bot : public Entity
{
public:
	float speed = 5.0f;
	float stopDistance = 10.0f;

	bool isSelected = false;

	bool hasCommand = false;
	Vector2D currentDestination = {0, 0};

	TransformComponent* transform = nullptr;
	RenderComponent* sprite = nullptr;

	Bot(Manager& manager, TransformComponent* target) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(150.0f, 350.0f);
		sprite = &addComponent<RenderComponent>("bot");
	}

	Bot(Manager& manager, TransformComponent* target, float x, float y) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(x, y);
		sprite = &addComponent<RenderComponent>("bot");
	}

	~Bot() {}
};
