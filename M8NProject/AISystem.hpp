#pragma once

#include "ECS.hpp"
#include "Entities.hpp"

class AISystem : public System
{
public:
	AISystem(Manager& manager) : System(manager) {}
	~AISystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override;
	void IACoreFunctionality(Unit* unitEntity);
	void changeTextureSelected(Unit* unitEntity);
	void selectUnits(Unit* unitEntity, Vector2D& cameraPos);
	void moveUnitsInput(Unit* unitEntity, Vector2D& cameraPos);
};