#pragma once

#include "Entity.h"
#include "Components.h"

class Player : public Entity
{
public:
	Player(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(200, 200);
		sprite = &addComponent<RenderComponent>("playerTexture");
		input = &addComponent<InputComponent>();

	}
	~Player() {}

	TransformComponent* transform;
	RenderComponent* sprite;
	InputComponent* input;
};
