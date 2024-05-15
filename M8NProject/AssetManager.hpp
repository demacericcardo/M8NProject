#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <map>

class AssetManager
{
private:
	AssetManager() {}

	std::map<std::string, SDL_Texture*> textures;
public:
	AssetManager(const AssetManager&) = delete;
	void operator=(const AssetManager&) = delete;
	~AssetManager();

	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}

	bool addTexture(std::string id, const char* filePath);
	SDL_Texture* getTexture(std::string id);
};