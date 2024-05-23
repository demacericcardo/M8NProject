#pragma once

#include "Entity.hpp"
#include "Components.hpp"

class Player : public Entity
{
private:
	SDL_Rect srcRect = { 0, 0, 32, 32 };
public:
	float speed = 250.0f;
	int minerals = 0;

	TransformComponent* transform;
	RenderComponent* sprite;
	StateComponent<PlayerState>* state;
	AnimationComponent* animation;
	ColliderComponent* collider;

	bool hasInteracted = false;
	Entity* interactableEntity = nullptr;

	Player(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(200.0f, 200.0f);

		sprite = &addComponent<RenderComponent>("playerTexture", srcRect, 2);
		sprite->zIndex = 100;

		state = &addComponent<StateComponent<PlayerState>>(PlayerState::IDLE);
		animation = &addComponent<AnimationComponent>("playerIdle");
		collider = &addComponent<ColliderComponent>(static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), sprite->width, sprite->height, "player");
	}
	~Player() {}
};
