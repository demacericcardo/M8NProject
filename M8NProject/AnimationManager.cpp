#include "AnimationManager.hpp"

bool AnimationManager::addAnimation(std::string animationName, int index, int frames, int speed)
{
	bool result = false;

	try
	{
		std::unique_ptr<Animation> animation = std::make_unique<Animation>(index, frames, speed);
		animations[animationName] = std::move(animation);
		result = true;
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "AnimationManager: Memory allocation failed: " << e.what() << '\n';
	}
	catch (const std::length_error& e)
	{
		std::cerr << "AnimationManager: Maximum size for map exceeded: " << e.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "AnimationManager: An unknown error occurred.\n";
	}

	return result;
}

Animation* AnimationManager::getAnimation(std::string animationName)
{
	return animations[animationName].get();
}