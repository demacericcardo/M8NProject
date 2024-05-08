#include "Game.h"
#include "ECS.h"
#include "Managers.h"
#include "Entities.h"
#include "Systems.h"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

const Uint8* Game::currentKeyStates = nullptr;

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

	if (!AssetManager::getInstance().addTexture("playerTexture", "assets/pgUp.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}

	RenderSystem& renderSystem = manager.addSystem<RenderSystem>(manager);
	InputSystem& inputSystem = manager.addSystem<InputSystem>(manager);

	Player& player = manager.addEntity<Player>(manager);
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

	currentKeyStates = SDL_GetKeyboardState(NULL);
}

void Game::update() {
	manager.refresh();
	manager.update();
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned..." << std::endl;
}