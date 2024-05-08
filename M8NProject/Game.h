#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void clean();

	bool running() const { return isRunning; }

	static const Uint8* currentKeyStates;

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	bool isRunning;
	SDL_Window* window;
};