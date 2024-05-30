#pragma once

#include "InputSystem.hpp"
#include "Input.hpp"

void InputSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Input& input = Input::getInstance();

	input.up = input.currentKeyStates[SDL_SCANCODE_W];
	input.down = input.currentKeyStates[SDL_SCANCODE_S];
	input.left = input.currentKeyStates[SDL_SCANCODE_A];
	input.right = input.currentKeyStates[SDL_SCANCODE_D];
	input.interact = input.currentKeyStates[SDL_SCANCODE_E];

	input.mouseLeftClick = input.mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);
	input.mouseRightClick = input.mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT);

	if (input.mouseLeftClick)
	{
		if (!input.mousePosClicked)
			input.mousePosClicked = Vector2D(static_cast<float>(input.mouseXPos), static_cast<float>(input.mouseYPos));
	}
	else
	{
		input.mousePosClicked.reset();
	}
}