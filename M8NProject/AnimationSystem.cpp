#include "AnimationSystem.hpp"

void AnimationSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	Uint32 currentTime = SDL_GetTicks();

	for (auto& entity : entities)
	{
		if (entity->hasComponent<AnimationComponent>() && entity->hasComponent<RenderComponent>())
		{
			AnimationComponent& const animation = entity->getComponent<AnimationComponent>();
			RenderComponent& render = entity->getComponent<RenderComponent>();

			Animation* animationData = animation.getAnimation();
			if (animationData) {
				render.srcRect.y = animationData->index * render.height;

				if (currentTime > animation.lastUpdate + animationData->speed) {
					animation.frameCounter = (animation.frameCounter + 1) % animationData->frames;
					animation.lastUpdate = currentTime;
				}

				render.srcRect.x = animation.frameCounter * render.width;
			}
		}
	}
}