#pragma once

#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <memory>

#include "Component.hpp"
#include "Components.hpp"

class Manager;
class Component;

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

using ComponentID = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray{};
	ComponentBitSet componentBitSet;

public:
	Entity(Manager& mManager) : manager(mManager) {}
	virtual ~Entity() {}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs)
	{
		auto component = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
		component->setEntity(this);
		auto componentRawPointer = component.get();

		auto componentTypeID = getComponentTypeID<T>();
		componentArray[componentTypeID] = componentRawPointer;
		componentBitSet[componentTypeID] = true;

		components.emplace_back(std::move(component));

		return *componentRawPointer;
	}

	template <typename T> T& getComponent() const
	{
		auto componentRawPointer(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(componentRawPointer);
	}

	template <typename T> std::vector<T*> getComponents() const
	{
		static_assert(std::is_base_of<Component, T>::value, "");
		std::vector<T*> result;
		for (const auto& component : components)
		{
			if (T* casted = dynamic_cast<T*>(component.get()))
			{
				result.push_back(casted);
			}
		}
		return result;
	}

	bool hasColliderComponent(const std::string& tag)
	{
		for (auto& component : components)
		{
			ColliderComponent* collider = dynamic_cast<ColliderComponent*>(component.get());
			if (collider && collider->tag == tag)
				return true;
		}
		return false;
	}

	ColliderComponent& getColliderComponent(const std::string& tag)
	{
		for (auto& component : components)
		{
			ColliderComponent* collider = dynamic_cast<ColliderComponent*>(component.get());
			if (collider && collider->tag == tag)
				return *collider;
		}
		throw std::runtime_error("No ColliderComponent with tag " + tag + " found.");
	}
};
