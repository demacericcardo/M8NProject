#pragma once

#include "ECS.h"
#include "Enums.h"

class StateComponent : public Component
{
private:
	State state;
public:
	StateComponent(State initialState) :state(initialState) {}

	State getState() const { return state; }
	void setState(State newState) { state = newState; }
};