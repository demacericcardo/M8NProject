#pragma once

#include "ECS.hpp"
#include "Enums.hpp"

template <typename EnumType>
class StateComponent : public Component
{
private:
    EnumType previousState;
    EnumType state;
public:
    StateComponent(EnumType initialState) :state(initialState), previousState(initialState) {}

    EnumType getState() const { return state; }
    bool hasStateChanged() const { return state != previousState; }
    void setState(EnumType newState)
    {
        previousState = state;
        state = newState;
    }
};