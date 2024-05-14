#pragma once

#include <string>

#include "ECS.hpp"

class RenderComponent : public Component
{
private:
	std::string textureID;
public:
	int zIndex = 0;

	SDL_Rect srcRect = { 0, 0, 32, 32 };
	SDL_Rect destRect = { 0, 0, 32, 32 };

	int height = 32;
	int width = 32;
	int scale = 1;

	RenderComponent(std::string texId)
		: textureID(texId) {}

	RenderComponent(std::string texId, int index)
		: textureID(texId), zIndex(index) {}

	RenderComponent(std::string texId, SDL_Rect srcR, SDL_Rect destR)
		: textureID(texId), srcRect(srcR), destRect(destR) {}

	RenderComponent(std::string texId, SDL_Rect srcR, SDL_Rect destR, int h, int w, int s)
		: textureID(texId), srcRect(srcR), destRect(destR), height(h), width(w), scale(s) {}

	std::string getTextureID() { return textureID; }
};