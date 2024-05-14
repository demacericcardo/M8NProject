#include "Game.hpp"
#include "ECS.hpp"
#include "Managers.hpp"
#include "Entities.hpp"
#include "Systems.hpp"
#include "Camera.hpp"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

const Uint8* Game::currentKeyStates = nullptr;

Uint32 Game::mouseState = 0;
int Game::mouseXPos = 0;
int Game::mouseYPos = 0;

Game::Game() : isRunning(false), window(nullptr) {}
Game::~Game() {}

void Game::init(const char* title, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	loadTextures();

	Rock& rock = manager.addEntity<Rock>(manager);
	Player& player = manager.addEntity<Player>(manager);
	Bot& bot = manager.addEntity<Bot>(manager, player.transform);

	RenderSystem& renderSystem = manager.addSystem<RenderSystem>(manager);
	InputSystem& inputSystem = manager.addSystem<InputSystem>(manager);
	CollisionSystem& collisionSystem = manager.addSystem<CollisionSystem>(manager);
	AISystem& aiSystem = manager.addSystem<AISystem>(manager);

	Camera::getInstance().setTarget(player.getComponent<TransformComponent>());
}

void Game::loadTextures()
{
	if (!AssetManager::getInstance().addTexture("playerTexture", "assets/character.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}

	if (!AssetManager::getInstance().addTexture("trigger", "assets/trigger.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}

	if (!AssetManager::getInstance().addTexture("rockTexture", "assets/dirt.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}

	if (!AssetManager::getInstance().addTexture("mineralInterface", "assets/water.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}
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

	Game::mouseState = SDL_GetMouseState(&Game::mouseXPos, &Game::mouseYPos);
}

void Game::update() {
	manager.refresh();
	manager.update();
	Camera::getInstance().update();
}

void Game::clean()
{
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		if (strlen(SDL_GetError()) > 0) {
			std::cout << "SDL_DestroyRenderer Error: " << SDL_GetError() << std::endl;
			SDL_ClearError();
		}
	}

	if (window != nullptr) {
		SDL_DestroyWindow(window);
		if (strlen(SDL_GetError()) > 0) {
			std::cout << "SDL_DestroyWindow Error: " << SDL_GetError() << std::endl;
			SDL_ClearError();
		}
	}

	SDL_Quit();
	if (strlen(SDL_GetError()) > 0) {
		std::cout << "SDL_Quit Error: " << SDL_GetError() << std::endl;
		SDL_ClearError();
	}

	std::cout << "Game Cleaned..." << std::endl;
}