#include "game/Game.h"

#include <vector>

#include "ECS/Collision.h"
#include "ECS/Components.h"
#include "game/Map.h"
#include "game/TextureManager.h"

Map *map = nullptr;
Manager enitityManager;

auto &playerEntity(enitityManager.addEntity());
auto &wall(enitityManager.addEntity());

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

//
//
//
//

Game::Game(/* args */) { std::cout << "Game instantiated." << std::endl; }

Game::~Game() { clean(); }

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Initialized" << std::endl;
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    if (window) {
      std::cout << "Window created succesfully." << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
      std::cout << "Renderer created succesfully." << std::endl;
    }
    isRunning = true;

    // init game entities
    map = new Map();
    playerEntity.addComponent<TransformComponent>(2);
    playerEntity.addComponent<SpriteComponent>("assets/man.png");
    playerEntity.addComponent<KeyboardController>();
    playerEntity.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
  }
}

void Game::update() {
  enitityManager.refresh();
  enitityManager.update();

  auto &playerCollider =
      playerEntity.getComponent<ColliderComponent>().collider;
  auto &wallCollider = wall.getComponent<ColliderComponent>().collider;

  if (Collision::AABBcollision(playerCollider, wallCollider)) {
    std::cout << "collision detected" << std::endl;
  }
}

void Game::handleEvents() {
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  ///----- main render

  SDL_SetRenderDrawColor(renderer, 130, 230, 60, 255);

  // map->DrawMap();
  enitityManager.draw();
  /// ------
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "Game cleaned succesfully." << std::endl;
}