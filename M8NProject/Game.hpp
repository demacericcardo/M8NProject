#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
public:
	Game();
	~Game();

	void init(const char* title, bool fullscreen);
	void renderTiles();
	void initSystems();
	void handleEvents();
	void update(float deltaTime);
	void render(float interpolation);
	void clean();
	void loadTextures();
	void loadAnimations();

	bool running() const { return isRunning; }

	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 720;

	static const int TILE_SIZE = 32;

	static float frameLength;
	static float interpolation;

	static SDL_Renderer* renderer;
	static SDL_Event event;
};