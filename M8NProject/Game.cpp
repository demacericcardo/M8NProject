#include "Game.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "AssetManager.h"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());

Game::Game() : isRunning(false), window(nullptr) {}
Game::~Game() {}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	if (!AssetManager::getInstance().addTexture("playerTexture", "path/to/player/image.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}
	player.addComponent<TransformComponent>(100, 100, 32, 32, 1);
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}