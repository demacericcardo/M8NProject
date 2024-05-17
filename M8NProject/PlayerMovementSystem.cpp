#include "PlayerMovementSystem.hpp"
#include "Input.hpp"
#include "Player.hpp"
#include "ParticleEmitter.hpp"

void PlayerMovementSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Input& input = Input::getInstance();

	for (auto& entity : entities)
	{
		Player* playerEntity = dynamic_cast<Player*>(entity.get());

		if (playerEntity)
		{
			TransformComponent& transform = playerEntity->getComponent<TransformComponent>();
			StateComponent& state = playerEntity->getComponent<StateComponent>();
			RenderComponent& render = playerEntity->getComponent<RenderComponent>();

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
			{
				render.isFlipped = transform.velocity.x > 0;

				state.setState(PlayerState::WALK);
				if (!ParticleEmitter::getInstance().hasParticleByTextureID("walkParticle"))
					ParticleEmitter::getInstance().emitParticle("walkParticle", transform.position, Vector2D(0, 0), 0.025f);
			}
			else
			{
				state.setState(PlayerState::IDLE);
			}

			transform.previousPosition = transform.position;
			transform.position.x += transform.velocity.x * static_cast<float>(transform.speed);
			transform.position.y += transform.velocity.y * static_cast<float>(transform.speed);

		}
	}
}