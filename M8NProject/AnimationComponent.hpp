#pragma once

#include "ECS.hpp"

class AnimationComponent : public Component
{
public:
	int index;
	int frames;
	int speed;

	AnimationComponent(int i, int f, int s) : index(i), frames(f), speed(s) {}
	~AnimationComponent() {}
};