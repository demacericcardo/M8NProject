#pragma once
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>

class InteractionManager
{
public:
	static InteractionManager& getInstance()
	{
		static InteractionManager instance;
		return instance;
	}
	~InteractionManager() {}

private:
	InteractionManager() {}
	InteractionManager(const InteractionManager&) = delete;
	void operator=(const InteractionManager&) = delete;
};