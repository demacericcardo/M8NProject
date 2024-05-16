#pragma once

#include <string>

#include "ECS.hpp"
#include "Particle.hpp"

class ParticleComponent : public Component
{
private:
	Particle* currentParticle = nullptr;
public:

	ParticleComponent() {}
	~ParticleComponent() {}

	Particle* getParticle() { return currentParticle; }
	void setParticle(std::string particleName) { currentParticle = ParticleManager::getInstance().getParticle(particleName); }
};