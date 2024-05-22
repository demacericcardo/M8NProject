#pragma once

#include "ECS.hpp"
#include "Enums.hpp"

class StateComponent : public Component
{
private:
	PlayerState previousState;
	PlayerState state;
public:
	StateComponent(PlayerState initialState) :state(initialState), previousState(initialState) {}

	PlayerState getState() const { return state; }
	bool hasStateChanged() const { return state != previousState; }
	void setState(PlayerState newState)
	{
		previousState = state;
		state = newState;
	}
};