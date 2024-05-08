#pragma once

#include <string>

#include "ECS.h"

class RenderComponent : public Component
{

public:
	std::string textureID;

	RenderComponent(std::string texId)
	{
		textureID = texId;
	};
};