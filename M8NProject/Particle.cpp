#include "Particle.hpp"
#include "Game.hpp"

void Particle::update() {
	position += velocity * Game::deltaTime;
	remainingLifeSpan -= Game::deltaTime;
}

bool Particle::isDead() const {
	return remainingLifeSpan <= 0;
}

float Particle::getRemainingLifetimeRatio() const {
	return remainingLifeSpan / totalLifeSpan;
}