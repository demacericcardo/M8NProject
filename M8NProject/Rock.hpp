#pragma once

#include "Entity.hpp"
#include "Components.hpp"
#include "ParticleEmitter.hpp"

class Rock : public Entity
{
private:
	int minerals = 10;
public:
	TransformComponent* transform;
	RenderComponent* sprite;
	ColliderComponent* collider;
	ColliderComponent* colliderHighlight;

	Rock(Manager& manager) : Entity(manager)
	{
		transform = &addComponent<TransformComponent>(100.0f, 100.0f);
		sprite = &addComponent<RenderComponent>("rock");
		colliderHighlight = &addComponent<ColliderComponent>(transform, sprite->width, sprite->height, "targetCollider");
		collider = &addComponent<ColliderComponent>(transform, sprite->width, sprite->height, "notwalkable");
	}
	~Rock() {}

	void takeMineral() {
		minerals--;
		if (minerals <= 0) {
			ParticleEmitter::getInstance().emitParticle("walkParticle", transform->position, Vector2D(0, 0), 2.0f);
			destroy();
		}
	}
};
