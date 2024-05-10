#pragma once

#include "Entity.h"

class Manager;

class System
{
private:
	Manager& manager;
public:
	bool active = true;

	System(Manager& mManager) : manager(mManager) {}
	virtual ~System() {}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	virtual void update(std::vector<std::unique_ptr<Entity>>& entities) {};
};