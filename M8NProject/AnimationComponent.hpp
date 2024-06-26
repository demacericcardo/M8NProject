#pragma once

#include <string>

#include "ECS.hpp"
#include "Animation.hpp"
#include "AnimationManager.hpp"

class AnimationComponent : public Component
{
private:
	Animation* currentAnimation = nullptr;
public:
	Uint32 lastUpdate = 0;
	int frameCounter = 0;

	AnimationComponent() { }
	AnimationComponent(std::string animationName) { currentAnimation = AnimationManager::getInstance().getAnimation(animationName); }
	~AnimationComponent() {}

	Animation* getAnimation() { return currentAnimation; }
	void setAnimation(std::string animationName) { currentAnimation = AnimationManager::getInstance().getAnimation(animationName); }
};