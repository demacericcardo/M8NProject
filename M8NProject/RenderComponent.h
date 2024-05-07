#pragma once

#include <string>

#include "ECS.h"

class RenderComponent : public Component
{

public:
	std::string textureID;
	int width, height = 32;
	int srcX, srcY = 0;

	RenderComponent(std::string texId, int w, int h, int x, int y)
	{
		textureID = texId;
		width = w;
		height = h;
		srcX = x;
		srcY = y;
	};
};