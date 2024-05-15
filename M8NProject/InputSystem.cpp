#pragma once

#include "InputSystem.hpp"
#include "Input.hpp"

void InputSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Input& input = Input::getInstance();

	input.up = Game::currentKeyStates[SDL_SCANCODE_W];
	input.down = Game::currentKeyStates[SDL_SCANCODE_S];
	input.left = Game::currentKeyStates[SDL_SCANCODE_A];
	input.right = Game::currentKeyStates[SDL_SCANCODE_D];
	input.interact = Game::currentKeyStates[SDL_SCANCODE_E];

	input.mouseLeftClick = Game::mouseState & SDL_BUTTON(SDL_BUTTON_LEFT);

	if (input.mouseLeftClick)
	{
		if (!input.mousePosClicked)
		{
			input.mousePosClicked = std::make_unique<Vector2D>(static_cast<float>(Game::mouseXPos), static_cast<float>(Game::mouseYPos));
		}
	}
	else
	{
		input.mousePosClicked.reset();
	}
}