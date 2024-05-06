#pragma once

class Entity;

class Component
{
private:
	Entity* entity;
public:
	Component() : entity(nullptr) {}
	virtual ~Component() {}

	void setEntity(Entity* e) { entity = e; }
	Entity* getEntity() const { return entity; }

	virtual void update() {}
};