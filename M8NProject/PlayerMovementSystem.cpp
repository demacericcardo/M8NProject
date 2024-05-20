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

			if (transform.velocity.x != 0 || transform.velocity.y != 0)
			{
				transform.velocity = transform.velocity.normalize();
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
			transform.position.x += transform.velocity.x * playerEntity->speed * Game::frameLength;
			transform.position.y += transform.velocity.y * playerEntity->speed * Game::frameLength;
		}
	}
}