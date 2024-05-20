#include "AnimationSystem.hpp"

void AnimationSystem::update(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto& entity : entities)
	{
		if (entity->hasComponent<AnimationComponent>() && entity->hasComponent<RenderComponent>())
		{
			AnimationComponent& const animation = entity->getComponent<AnimationComponent>();
			RenderComponent& render = entity->getComponent<RenderComponent>();

			Animation* animationData = animation.getAnimation();
			if (animationData) {
				render.srcRect.y = animationData->index * render.height;
				render.srcRect.x = render.srcRect.w * static_cast<int>((SDL_GetTicks() / animationData->speed) % animationData->frames);
			}
		}
	}
}