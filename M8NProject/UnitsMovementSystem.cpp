#include "UnitsMovementSystem.hpp"
#include "Unit.hpp"

void UnitsMovementSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity : entities)
	{
		Unit* unitEntity = dynamic_cast<Unit*>(entity.get());

		if (unitEntity)
		{
			TransformComponent& transform = unitEntity->getComponent<TransformComponent>();

			if (transform.velocity.x != 0 || transform.velocity.y != 0)
				transform.velocity = transform.velocity.normalize();

			transform.previousPosition = transform.position;
			transform.position.x += transform.velocity.x * unitEntity->speed * Game::frameLength;
			transform.position.y += transform.velocity.y * unitEntity->speed * Game::frameLength;

		}
	}
}