#include "UnitsMovementSystem.hpp"
#include "Bot.hpp"

void UnitsMovementSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity : entities)
	{
		Bot* botEntity = dynamic_cast<Bot*>(entity.get());

		if (botEntity)
		{
			TransformComponent& transform = botEntity->getComponent<TransformComponent>();

			if (transform.velocity.x != 0 && transform.velocity.y != 0)
			{
				float length = sqrt(transform.velocity.x * transform.velocity.x + transform.velocity.y * transform.velocity.y);
				transform.velocity.x /= length;
				transform.velocity.y /= length;
			}

			transform.previousPosition = transform.position;
			transform.position.x += transform.velocity.x * static_cast<float>(transform.speed);
			transform.position.y += transform.velocity.y * static_cast<float>(transform.speed);

		}
	}
}