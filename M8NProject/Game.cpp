#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "Managers.hpp"
#include "Entities.hpp"
#include "Systems.hpp"
#include "Camera.hpp"
#include "Input.hpp"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

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

	Bot& bot1 = manager.addEntity<Bot>(manager, player.transform, 150.0f, 150.0f);
	Bot& bot2 = manager.addEntity<Bot>(manager, player.transform, 200.0f, 250.0f);
	Bot& bot3 = manager.addEntity<Bot>(manager, player.transform, 300.0f, 350.0f);
	Bot& bot4 = manager.addEntity<Bot>(manager, player.transform, 50.0f, 550.0f);

	RenderSystem& renderSystem = manager.addSystem<RenderSystem>(manager);
	InputSystem& inputSystem = manager.addSystem<InputSystem>(manager);
	CollisionSystem& collisionSystem = manager.addSystem<CollisionSystem>(manager);
	AISystem& aiSystem = manager.addSystem<AISystem>(manager);
	PlayerMovementSystem& playerMovementSystem = manager.addSystem<PlayerMovementSystem>(manager);
	PlayerInteractionSystem& playerInteractionSystem = manager.addSystem<PlayerInteractionSystem>(manager);
	UnitsMovementSystem& unitsMovementSystem = manager.addSystem<UnitsMovementSystem>(manager);

	Camera::getInstance().setTarget(player.getComponent<TransformComponent>());
	Input::getInstance();
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

	Input& input = Input::getInstance();
	input.currentKeyStates = SDL_GetKeyboardState(NULL);
	input.mouseState = SDL_GetMouseState(&input.mouseXPos, &input.mouseYPos);
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

	if (!AssetManager::getInstance().addTexture("bot", "assets/bot.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}


	if (!AssetManager::getInstance().addTexture("botSelected", "assets/botSelected.png"))
	{
		std::cout << "Failed to add texture to AssetManager.\n";
		isRunning = false;
		return;
	}
}