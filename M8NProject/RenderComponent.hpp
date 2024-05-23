#pragma once

#include <string>
#include <SDL.h>

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

	bool isFlipped = false;

	RenderComponent(std::string textureID)
		: textureID(textureID) {}

	RenderComponent(std::string textureID, SDL_Rect srcRect)
		: textureID(textureID), srcRect(srcRect) {}

	RenderComponent(std::string textureID, SDL_Rect srcRect, int scale)
		: textureID(textureID), srcRect(srcRect), width(srcRect.w), height(srcRect.h), scale(scale) {}

	void setTextureId(std::string textureId) { textureID = textureId; }
	std::string getTextureID() { return textureID; }
};