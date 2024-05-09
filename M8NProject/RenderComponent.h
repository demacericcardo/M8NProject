#pragma once

#include <string>

#include "ECS.h"

class RenderComponent : public Component
{

public:
	std::string textureID;

	int height = 32;
	int width = 32;
	int scale = 1;

	RenderComponent(std::string texId)
	{
		textureID = texId;
	};

	RenderComponent(std::string texId, int h, int w, int s)
	{
		textureID = texId;
		height = h;
		width = w;
		scale = s;
	};
};