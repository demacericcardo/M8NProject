#pragma once

#include "ECS.hpp"
#include "Particle.hpp"

class ParticleEmitter
{
private:
	std::vector<Particle> particles;
	
	ParticleEmitter() {}
public:
	ParticleEmitter(const ParticleEmitter&) = delete;
	ParticleEmitter& operator=(const ParticleEmitter&) = delete;

	static ParticleEmitter& getInstance()
	{
		static ParticleEmitter instance;
		return instance;
	}

	void emitParticle(std::string textureID, Vector2D position, Vector2D velocity, float lifespan);
	void emitParticle(std::string textureID, Vector2D position, int height, int width, Vector2D velocity, float lifespan);
	void update();

	bool hasParticleByTextureID(std::string textureID);
};