#pragma once

#include <SDL.h>
#include <string>

#include "Vector2D.hpp"

class Particle {
public:
	std::string textureID;
	float totalLifeSpan;
	float remainingLifeSpan;

	Vector2D position;
	int height = 32;
	int width = 32;

	Vector2D velocity;

	Particle(std::string textureID, Vector2D position, Vector2D velocity, float lifeSpan)
		: textureID(textureID), position(position), velocity(velocity), remainingLifeSpan(lifeSpan), totalLifeSpan(lifeSpan) {}

	Particle(std::string textureID, Vector2D position, int height, int width, Vector2D velocity, float lifeSpan)
		: textureID(textureID), position(position), height(height), width(width), velocity(velocity), remainingLifeSpan(lifeSpan), totalLifeSpan(lifeSpan) {}

	void update();
	bool isDead() const;
	float getRemainingLifetimeRatio() const;
};