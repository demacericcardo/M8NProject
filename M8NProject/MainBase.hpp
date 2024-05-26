#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class MainBase : public Entity
{
private:
	SDL_Rect srcRect = { 8, 176, 48, 40 };
public:
	TransformComponent* transform;
	RenderComponent* sprite;

	MainBase(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(500.0f, 500.0f);
		sprite = &addComponent<RenderComponent>("ambient", srcRect);
	}
	~MainBase() {}
};
