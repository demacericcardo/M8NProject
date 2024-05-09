#pragma once

#include "ECS.h"
#include "Enums.h"

class StateComponent : public Component
{
private:
	State state;
public:

	StateComponent(State initialState)
	{
		state = initialState;
	}

	void setState(State newState)
	{
		state = newState;
	}

	State getState() const
	{
		return state;
	}
};