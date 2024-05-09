#pragma once

#include "ECS.h"

class AnimationComponent : public Component
{
public:
	int index;
	int frames;
	int speed;

	AnimationComponent(int i, int f, int s) : index(i), frames(f), speed(s) {}
	~AnimationComponent() {}
};