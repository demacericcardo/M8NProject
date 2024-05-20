#pragma once
class Animation
{
public:
	int index;
	int frames;
	float speed;

	Animation(int index, int frames, float speed)
		: index(index), frames(frames), speed(speed) {}
};

