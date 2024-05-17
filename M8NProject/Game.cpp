#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "Managers.hpp"
#include "Entities.hpp"
#include "Systems.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "ParticleEmitter.hpp"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

float Game::deltaTime = 0.0f;

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
		SDL_ShowCursor(SDL_DISABLE);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	loadTextures();
	loadAnimations();

	Rock& rock = manager.addEntity<Rock>(manager);
	Player& player = manager.addEntity<Player>(manager);

	Bot& bot1 = manager.addEntity<Bot>(manager, player.transform, 150.0f, 150.0f);
	Bot& bot2 = manager.addEntity<Bot>(manager, player.transform, 200.0f, 250.0f);
	Bot& bot3 = manager.addEntity<Bot>(manager, player.transform, 300.0f, 350.0f);
	Bot& bot4 = manager.addEntity<Bot>(manager, player.transform, 50.0f, 550.0f);

	initSystems();

	Camera::getInstance().setTarget(player.getComponent<TransformComponent>());
	Input::getInstance();
}

void Game::renderTiles() {
	int startTileX = Camera::getInstance().getPosition().x / 32 - 2;
	int startTileY = Camera::getInstance().getPosition().y / 32 - 2;
	int endTileX = startTileX + (Game::SCREEN_WIDTH / 32) + 2;
	int endTileY = startTileY + (Game::SCREEN_HEIGHT / 32) + 2;

	for (int y = startTileY; y < endTileY; y++) {
		for (int x = startTileX; x < endTileX; x++) {
			//Tile& tile = map.getTile(x, y);
			SDL_Rect destRect = { (x * 32) - Camera::getInstance().getPosition().x, (y * 32) - Camera::getInstance().getPosition().y, 32, 32 };
			SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture("ground"), NULL, &destRect);
		}
	}
}


void Game::initSystems()
{
	manager.addSystem<RenderSystem>(manager);
	manager.addSystem<InputSystem>(manager);
	manager.addSystem<CollisionSystem>(manager);
	manager.addSystem<AISystem>(manager);
	manager.addSystem<PlayerMovementSystem>(manager);
	manager.addSystem<PlayerInteractionSystem>(manager);
	manager.addSystem<UnitsMovementSystem>(manager);
	manager.addSystem<StateAnimationSystem>(manager);
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

	Uint32 start_time = SDL_GetTicks();

	manager.refresh();

	SDL_RenderClear(Game::renderer);

	Camera::getInstance().update();

	renderTiles();

	ParticleEmitter::getInstance().update();

	manager.update();

	/*
	Input& input = Input::getInstance();

	SDL_Rect cursorRect = { input.mouseXPos, input.mouseYPos, 32, 32 };
	SDL_Rect srcRect = { 0, 0, 32, 32 };

	SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture("cursor"), &srcRect, &cursorRect);
	*/

	SDL_RenderPresent(Game::renderer);

	Uint32 end_time = SDL_GetTicks();
	Game::deltaTime = (end_time - start_time) / 1000.0f;
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
	std::vector<std::pair<std::string, std::string>> textures = {
		{"playerTexture", "assets/character.png"},
		{"trigger", "assets/trigger.png"},
		{"rockTexture", "assets/dirt.png"},
		{"bot", "assets/bot.png"},
		{"botSelected", "assets/botSelected.png"},
		{"walkParticle", "assets/walkParticle.png"},
		{ "cursor", "assets/cursor.png" },
		{ "ground", "assets/ground.png" }
	};

	for (const auto& texture : textures)
	{
		if (!AssetManager::getInstance().addTexture(texture.first, texture.second.c_str()))
		{
			std::cout << "Failed to add texture to AssetManager.\n";
			isRunning = false;
			return;
		}
	}
}

void Game::loadAnimations()
{
	std::vector<std::tuple<std::string, int, int, int>> animations = {
		{"playerIdle", 0, 2, 200},
		{"playerWalk", 1, 4, 150},
		{"botIdle", 0, 2, 200}
	};

	for (const auto& animation : animations)
	{
		if (!AnimationManager::getInstance().addAnimation(std::get<0>(animation), std::get<1>(animation), std::get<2>(animation), std::get<3>(animation)))
		{
			std::cout << "Failed to add animation to AnimationManager.\n";
			isRunning = false;
			return;
		}
	}
}