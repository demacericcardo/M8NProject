#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int maxFrameLenght = 1000 / FPS;

	Uint32 frameStart;
	int frameLength;

	game = new Game();

	game->init("Game Window", false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		frameLength = SDL_GetTicks() - frameStart;
		float deltaTime = frameLength / 1000.0f;
		
		game->handleEvents();
		game->update();

		if (maxFrameLenght > frameLength)
			SDL_Delay(maxFrameLenght - frameLength);
	}

	game->clean();

	delete game;

	return 0;
}