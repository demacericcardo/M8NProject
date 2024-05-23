#pragma once

#include "ECS.hpp"
#include "Entities.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem(Manager& manager) : System(manager) {}
	~CollisionSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;

	void checkUnitsCollisions(std::unique_ptr<Entity>& entity2, Unit* unitEntity, std::vector<std::unique_ptr<Entity>>& entities, std::unique_ptr<Entity>& entity1);

	void checkPlayerCollisions(std::unique_ptr<Entity>& entity2, ColliderComponent& collider1, Player* playerEntity);

	bool collidesWith(const ColliderComponent& first, const ColliderComponent& second);
};