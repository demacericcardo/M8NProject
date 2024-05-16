#include "AssetManager.hpp"
#include "Game.hpp"

AssetManager::~AssetManager()
{
	for (auto& pair : textures)
		SDL_DestroyTexture(pair.second);
}

bool AssetManager::addTexture(std::string id, const char* filePath)
{

	SDL_Surface* tempSurface = IMG_Load(filePath);
	if (!tempSurface)
	{
		std::cerr << "AssetManager: Failed to load image. SDL_image Error: " << IMG_GetError() << '\n';
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	if (!tex)
	{
		std::cerr << "AssetManager: Failed to create texture. SDL Error: " << SDL_GetError() << '\n';
		return false;
	}

	textures[id] = tex;
	return true;
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
	return textures[id];
}