#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include "Entity.h"
#include "System.h"

class Entity;
class System;

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<System>> systems;

public:
	void update()
	{
		for (auto& s : systems)
		{
			s->update(entities);
		}
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

	template <typename T, typename... TArgs>
	T& addEntity(TArgs&&... args)
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must be a derived class of Entity");

		auto uPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
		auto* e = uPtr.get();
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

	template <typename T, typename... TArgs>
	T& addSystem(TArgs&&... args)
	{
		static_assert(std::is_base_of<System, T>::value, "T must be a derived class of System");

		auto uPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
		auto* e = uPtr.get();
		systems.emplace_back(std::move(uPtr));
		return *e;
	}
};
