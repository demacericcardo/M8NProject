#include "Particle.hpp"
#include "Game.hpp"

void Particle::update() {
	position += velocity * Game::frameLength;
	remainingLifeSpan -= Game::frameLength;
}

bool Particle::isDead() const {
	return remainingLifeSpan <= 0;
}

float Particle::getRemainingLifetimeRatio() const {
	return remainingLifeSpan / totalLifeSpan;
}