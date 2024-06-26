#pragma once

#include <nlohmann/json.hpp>
#include <fstream>

#include "Game.hpp"
#include "ECS.hpp"
#include "Managers.hpp"
#include "Entities.hpp"
#include "Systems.hpp"
#include "RenderSystems.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "ParticleEmitter.hpp"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

float Game::frameLength = 0.0f;
float Game::interpolation = 0.0f;

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

		SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
		SDL_ShowCursor(SDL_DISABLE);

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	initTextures();
	initAnimations();

	Rock& rock = manager.addEntity<Rock>(manager);
	Player& player = manager.addEntity<Player>(manager);

	Unit& bot1 = manager.addEntity<Unit>(manager, 0.0f, 0.0f);
	Unit& bot2 = manager.addEntity<Unit>(manager, 200.0f, 250.0f);
	Unit& bot3 = manager.addEntity<Unit>(manager, 300.0f, 350.0f);
	Unit& bot4 = manager.addEntity<Unit>(manager, 50.0f, 550.0f);

	MainBase& mainBase = manager.addEntity<MainBase>(manager);

	initSystems();

	Camera::getInstance().setTarget(player.getComponent<TransformComponent>());
	Input::getInstance();
}

void Game::initSystems()
{
	manager.addSystem<InputSystem>(manager);
	manager.addSystem<CollisionSystem>(manager);
	manager.addSystem<AISystem>(manager);
	manager.addSystem<PlayerMovementSystem>(manager);
	manager.addSystem<PlayerInteractionSystem>(manager);
	manager.addSystem<UnitsMovementSystem>(manager);
	manager.addSystem<StateAnimationSystem>(manager);
	manager.addSystem<AnimationSystem>(manager);
	manager.addSystem<MouseOverlaySystem>(manager);
	manager.addSystem<ColliderLocationSystem>(manager);

	manager.addRenderSystem<BaseRenderSystem>(manager);
}

void Game::initTextures()
{
	std::vector<std::pair<std::string, std::string>> textures = {
		{"playerTexture", "assets/character.png"},
		{"rock", "assets/rock.png"},
		{"rockHighlighted", "assets/rockHighlighted.png"},
		{"bot", "assets/bot.png"},
		{"botSelected", "assets/botSelected.png"},
		{"walkParticle", "assets/walkParticle.png"},
		{"selectionParticle", "assets/selectionParticle.png"},
		{ "cursor", "assets/cursor.png" },
		{ "ambient", "assets/ambient.png"}
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

void Game::initAnimations()
{
	std::vector<std::tuple<std::string, int, int, int>> animations = {
		{"playerIdle", 0, 2, 200.0f},
		{"playerWalk", 3, 4, 150.0f},
		{"unitIdle", 0, 4, 200.0f},
		{"unitWalk", 2, 4, 200.0f}
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

	if (input.currentKeyStates[SDL_SCANCODE_ESCAPE])
		isRunning = false;

	input.mouseState = SDL_GetMouseState(&input.mouseXPos, &input.mouseYPos);
}

void Game::update(float frameLenght) {

	Game::frameLength = frameLenght;
	manager.refresh();
	manager.update();
	Camera::getInstance().update();
}

void Game::render(float interpolation)
{
	Game::interpolation = interpolation;

	SDL_RenderClear(renderer);

	renderTiles();
	ParticleEmitter::getInstance().render();
	manager.render();
	renderMouse();

	SDL_RenderPresent(renderer);
}

void Game::renderTiles() {
	/*Camera& camera = Camera::getInstance();

	std::ifstream i("assets/mainMapData.json");
	nlohmann::json j;
	i >> j;

	int startTileX = (static_cast<int>(camera.getPosition().x) / Game::TILE_SIZE) - Game::TILE_SIZE;
	int startTileY = (static_cast<int>(camera.getPosition().y) / Game::TILE_SIZE) - Game::TILE_SIZE;
	int endTileX = startTileX + (Game::SCREEN_WIDTH / Game::TILE_SIZE) + (Game::TILE_SIZE * 2);
	int endTileY = startTileY + (Game::SCREEN_HEIGHT / Game::TILE_SIZE) + (Game::TILE_SIZE * 2);

	int initialX = startTileX * Game::TILE_SIZE - static_cast<int>(camera.getPosition().x);
	int initialY = startTileY * Game::TILE_SIZE - static_cast<int>(camera.getPosition().y);

	for (int y = startTileY, destY = initialY; y < endTileY; y++, destY += Game::TILE_SIZE) {
		for (int x = startTileX, destX = initialX; x < endTileX; x++, destX += Game::TILE_SIZE) {
			for (auto& frame : j["frames"]) {
				SDL_Rect srcRect = { frame["frame"]["x"], frame["frame"]["y"], frame["frame"]["w"], frame["frame"]["h"] };
				SDL_Rect destRect = { destX, destY, Game::TILE_SIZE, Game::TILE_SIZE };
				SDL_Texture* texture = AssetManager::getInstance().getTexture(frame["filename"]);
				SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
			}
		}
	}*/
}

void Game::renderMouse()
{
	Input& input = Input::getInstance();

	SDL_Rect srcRect = { 0, 0, CURSOR_WIDTH, CURSOR_HEIGHT };
	SDL_Rect destRect = { input.mouseXPos - CURSOR_WIDTH / 2, input.mouseYPos - CURSOR_HEIGHT / 2, CURSOR_WIDTH, CURSOR_HEIGHT };

	SDL_RenderCopy(Game::renderer, AssetManager::getInstance().getTexture("cursor"), &srcRect, &destRect);
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