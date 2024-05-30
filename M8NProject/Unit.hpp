#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Unit : public Entity
{
private:
	SDL_Rect srcRect = { 0, 0, 32, 32 };
public:
	float speed = 250.0f;

	bool isSelected = false;
	bool isOverlapped = false;

	std::optional<Vector2D> currentDestination;
	TransformComponent* currentTarget = nullptr;

	TransformComponent* transform = nullptr;
	RenderComponent* sprite = nullptr;
	AnimationComponent* animation = nullptr;
	StateComponent<UnitState>* state = nullptr;
	ColliderComponent* collider = nullptr;

	Unit(Manager& manager, float x, float y) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(x, y);
		sprite = &addComponent<RenderComponent>("bot", srcRect);
		animation = &addComponent<AnimationComponent>("unitIdle");
		state = &addComponent<StateComponent<UnitState>>(UnitState::IDLE);
		collider = &addComponent<ColliderComponent>("selectableUnit");
	}

	~Unit() {}
};
