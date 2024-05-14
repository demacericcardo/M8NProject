#pragma once

#include "InputSystem.hpp"

void InputSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity : entities)
	{
		if (entity->hasComponent<InputComponent>() && entity->hasComponent<TransformComponent>() && entity->hasComponent<StateComponent>())
		{
			InputComponent& input = entity->getComponent<InputComponent>();
			TransformComponent& transform = entity->getComponent<TransformComponent>();
			StateComponent& state = entity->getComponent<StateComponent>();

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

			if (input.up == input.down)
				transform.velocity.y = 0.0f;
			else if (input.up)
				transform.velocity.y = -1.0f;
			else if (input.down)
				transform.velocity.y = 1.0f;

			if (input.left == input.right)
				transform.velocity.x = 0.0f;
			else if (input.left)
				transform.velocity.x = -1.0f;
			else if (input.right)
				transform.velocity.x = 1.0f;

			if (transform.velocity.x != 0 && transform.velocity.y != 0)
			{
				float length = sqrt(transform.velocity.x * transform.velocity.x + transform.velocity.y * transform.velocity.y);
				transform.velocity.x /= length;
				transform.velocity.y /= length;
			}

			if (transform.velocity.x != 0 || transform.velocity.y != 0)
				state.setState(State::WALK);
			else
				state.setState(State::IDLE);

			if (input.interact)
			{
				Player* playerEntity = dynamic_cast<Player*>(entity.get());

				if (playerEntity && playerEntity->interactableEntity && !playerEntity->hasInteracted)
				{
					Rock* rockEntity = dynamic_cast<Rock*>(playerEntity->interactableEntity);
					rockEntity->takeMineral();
					playerEntity->minerals++;
					playerEntity->hasInteracted = true;
				}
			}
			else
			{
				Player* playerEntity = dynamic_cast<Player*>(entity.get());
				if (playerEntity)
				{
					playerEntity->hasInteracted = false;
					if (playerEntity->interactableEntity)
						playerEntity->interactableEntity = nullptr;
				}
			}

			transform.previousPosition = transform.position;
			transform.position.x += transform.velocity.x * static_cast<float>(transform.speed);
			transform.position.y += transform.velocity.y * static_cast<float>(transform.speed);
		}
	}
}