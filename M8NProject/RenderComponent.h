#pragma once

#include <string>

#include "ECS.h"

class RenderComponent : public Component
{
public:
	SDL_Rect srcRect = { 0, 0, 32, 32 };
	SDL_Rect destRect = { 0, 0, 32, 32 };
	std::string textureID;

	int height = 32;
	int width = 32;
	int scale = 1;

	RenderComponent(std::string texId)
		: textureID(texId) {}

	RenderComponent(std::string texId, SDL_Rect srcR, SDL_Rect destR)
		: textureID(texId), srcRect(srcR), destRect(destR) {}

	RenderComponent(std::string texId, SDL_Rect srcR, SDL_Rect destR, int h, int w, int s)
		: textureID(texId), srcRect(srcR), destRect(destR), height(h), width(w), scale(s) {}

};