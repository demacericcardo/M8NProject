#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int maxFrameLenght = 1000 / FPS;

	Uint32 frameStart;
	int frameLenght;

	game = new Game();

	game->init("Game Window", false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();

		frameLenght = SDL_GetTicks() - frameStart;

		if (maxFrameLenght > frameLenght)
			SDL_Delay(maxFrameLenght - frameLenght);
	}

	game->clean();

	delete game;

	return 0;
}