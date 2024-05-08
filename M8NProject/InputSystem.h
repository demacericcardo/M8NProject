#pragma once

#include <SDL.h>

#include "ECS.h"
#include "Game.h"
#include "Components.h"
#include "Managers.h"

class InputSystem : public System
{
public:
	InputSystem(Manager& manager) : System(manager) {}
	~InputSystem() {}

	void update(std::vector<std::unique_ptr<Entity>>& entities) override
	{
		for (auto& entity : entities)
		{
			if (entity->hasComponent<InputComponent>() && entity->hasComponent<TransformComponent>())
			{
				auto& input = entity->getComponent<InputComponent>();
				auto& transform = entity->getComponent<TransformComponent>();

				input.up = Game::currentKeyStates[SDL_SCANCODE_W];
				input.down = Game::currentKeyStates[SDL_SCANCODE_S];
				input.left = Game::currentKeyStates[SDL_SCANCODE_A];
				input.right = Game::currentKeyStates[SDL_SCANCODE_D];

				if (input.up)
				{
					transform.velocity.y = -1;
				}
				if (input.down)
				{
					transform.velocity.y = 1;
				}
				if (input.left)
				{
					transform.velocity.x = -1;
				}
				if (input.right)
				{
					transform.velocity.x = 1;
				}

				if (!input.up && !input.down)
				{
					transform.velocity.y = 0;
				}

				if (!input.left && !input.right)
				{
					transform.velocity.x = 0;
				}

				transform.position.x += transform.velocity.x * transform.speed;
				transform.position.y += transform.velocity.y * transform.speed;
			}
		}
	}
};