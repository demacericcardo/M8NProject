#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class Entity;

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		auto uPtr = std::make_unique<Entity>(*this);
		auto* e = uPtr.get();
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
