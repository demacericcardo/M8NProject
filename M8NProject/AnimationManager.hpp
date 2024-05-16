#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>

#include "Animation.hpp"

class AnimationManager
{
private:
	AnimationManager() {}

	std::map<std::string, std::unique_ptr<Animation>> animations;
public:
	AnimationManager(const AnimationManager&) = delete;
	void operator=(const AnimationManager&) = delete;

	static AnimationManager& getInstance()
	{
		static AnimationManager instance;
		return instance;
	}

	bool addAnimation(std::string animationName, int index, int frames, int speed);
	Animation* getAnimation(std::string animationName);
};