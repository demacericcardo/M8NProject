#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

#include "Entity.hpp"
#include "System.hpp"
#include "Camera.hpp"

class Entity;
class System;

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::unique_ptr<System>> systems;
	std::vector<std::unique_ptr<RenderSystem>> renderSystems;

public:
	void update()
	{
		for (auto& s : systems)
		{
			s->update(entities);
		}
	}

	void render()
	{
		for (auto& rs : renderSystems)
		{
			rs->render(entities);
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

		systems.erase(std::remove_if(std::begin(systems), std::end(systems),
			[](const std::unique_ptr<System>& mSystem)
			{
				return !mSystem->isActive();
			}),
			std::end(systems));

		renderSystems.erase(std::remove_if(std::begin(renderSystems), std::end(renderSystems),
			[](const std::unique_ptr<RenderSystem>& mRenderSystem)
			{
				return !mRenderSystem->isActive();
			}),
			std::end(renderSystems));
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

	template <typename T, typename... TArgs>
	T& addRenderSystem(TArgs&&... args)
	{
		static_assert(std::is_base_of<RenderSystem, T>::value, "T must be a derived class of RenderSystem");

		auto uPtr = std::make_unique<T>(std::forward<TArgs>(args)...);
		auto* e = uPtr.get();
		renderSystems.emplace_back(std::move(uPtr));
		return *e;
	}
};
