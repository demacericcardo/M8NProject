#pragma once

#include "Entity.h"

class Manager;

class System
{
private:
	Manager& manager;
public:
	System(Manager& mManager) : manager(mManager) {}
	virtual ~System() {}

	virtual void update(std::vector<std::unique_ptr<Entity>>& entities) {};
};