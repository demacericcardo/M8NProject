#include "ParticleEmitter.hpp"
#include "AssetManager.hpp"

void ParticleEmitter::emitParticle(std::string textureID, Vector2D position, Vector2D velocity, float lifespan) {
	particles.push_back(Particle(textureID, position, velocity, lifespan));
}

void ParticleEmitter::emitParticle(std::string textureID, Vector2D position, int height, int width, Vector2D velocity, float lifespan) {
	particles.push_back(Particle(textureID, position, height, width, velocity, lifespan));
}

void ParticleEmitter::render()
{
	for (Particle& particle : particles) {
		particle.update();
	}

	for (const Particle& particle : particles) {
		SDL_Rect srcRect = { 0, 0, particle.height, particle.width };
		Vector2D cameraPos = Camera::getInstance().getPosition();

		float scaleFactor = particle.getRemainingLifetimeRatio();
		int scaledWidth = static_cast<int>(particle.width * scaleFactor);
		int scaledHeight = static_cast<int>(particle.height * scaleFactor);

		int offsetX = (particle.width - scaledWidth) / 2;
		int offsetY = (particle.height - scaledHeight) / 2;

		SDL_Rect dstRect = { static_cast<int>(particle.position.x - cameraPos.x) + offsetX, static_cast<int>(particle.position.y - cameraPos.y) + offsetY, scaledWidth, scaledHeight };

		SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture(particle.textureID), &srcRect, &dstRect);
	}

	particles.erase(std::remove_if(particles.begin(), particles.end(),
		[](const Particle& particle) { return particle.isDead(); }), particles.end());
}

bool ParticleEmitter::hasParticleByTextureID(std::string textureID)
{
	return std::any_of(particles.begin(), particles.end(),
		[&textureID](const Particle& p) { return p.textureID == textureID; });
}