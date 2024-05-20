#include "Game.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const float frameLength = 1.0f / FPS;
	float accumulator = 0.0f;
	float interpolation = 0.0f;

	Uint32 currentTime = SDL_GetTicks();
	Uint32 previousTime;

	game = new Game();

	game->init("Game Window", false);

	while (game->running())
	{
		previousTime = currentTime;
		currentTime = SDL_GetTicks();

		float deltaTime = (currentTime - previousTime) / 1000.0f;

		accumulator += deltaTime;

		while (accumulator >= frameLength)
		{
			game->handleEvents();
			game->update(frameLength);

			accumulator -= frameLength;
		}

		interpolation = accumulator / frameLength;

		game->render(interpolation);
	}

	game->clean();

	delete game;

	return 0;
}