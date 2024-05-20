#pragma once

#include "Entity.hpp"

class Manager;

class RenderSystem
{
private:
	Manager& manager;
public:
	bool active = true;

	RenderSystem(Manager& mManager) : manager(mManager) {}
	virtual ~RenderSystem() {}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	virtual void render(std::vector<std::unique_ptr<Entity>>& entities) {};
};