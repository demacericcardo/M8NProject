#pragma once

#include "ECS.hpp"
#include "Enums.hpp"

class StateComponent : public Component
{
private:
	PlayerState state;
public:
	StateComponent(PlayerState initialState) :state(initialState) {}

	PlayerState getState() const { return state; }
	void setState(PlayerState newState) { state = newState; }
};