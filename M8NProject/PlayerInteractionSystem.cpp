#include "PlayerInteractionSystem.hpp"
#include "Player.hpp"
#include "Input.hpp"
#include "Rock.hpp"

void PlayerInteractionSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Input& input = Input::getInstance();

	for (auto& entity : entities)
	{
		Player* playerEntity = dynamic_cast<Player*>(entity.get());

		if (playerEntity)
		{
			if (input.interact)
			{
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
		}
	}
}