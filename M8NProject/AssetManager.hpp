#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>

class AssetManager
{
public:
	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}

	~AssetManager()
	{
		for (auto& pair : textures)
		{
			SDL_DestroyTexture(pair.second);
		}
	}

	bool addTexture(std::string id, const char* filePath)
	{
		SDL_Surface* tempSurface = IMG_Load(filePath);
		if (!tempSurface)
		{
			std::cout << "Failed to load image. SDL_image Error: " << IMG_GetError() << '\n';
			return false;
		}
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		if (!tex)
		{
			std::cout << "Failed to create texture. SDL Error: " << SDL_GetError() << '\n';
			return false;
		}
		textures[id] = tex;
		return true;
	}

	SDL_Texture* getTexture(std::string id)
	{
		return textures[id];
	}

private:
	AssetManager() {}
	AssetManager(const AssetManager&) = delete;
	void operator=(const AssetManager&) = delete;

	std::map<std::string, SDL_Texture*> textures;
};