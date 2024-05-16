#pragma once
class Animation
{
public:
	int index;
	int frames;
	int speed;

	Animation(int index, int frames, int speed)
		: index(index), frames(frames), speed(speed) {}
};

