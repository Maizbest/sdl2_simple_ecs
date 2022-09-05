#include "game/Game.h"

#include <string>
#include <vector>

#include "ECS/Collision.h"
#include "ECS/Components.h"
#include "game/TextureManager.h"

int Game::width = 800;
int Game::height = 600;

Manager enitityManager;

Map map("assets/terrains.png", 32, 2);

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;
SDL_Rect Game::camera = {0, 0, Game::width, Game::height};

auto &playerEntity(enitityManager.addEntity());
auto &tiles(enitityManager.getGroup(GroupLabel::MapGroup));
auto &players(enitityManager.getGroup(GroupLabel::PlayerGroup));
auto &colliders(enitityManager.getGroup(GroupLabel::CollisionGroup));

const std::string terrainTilesFile("assets/terrains.png");

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

    Game::width = width;
    Game::height = height;
    camera.w = Game::width;
    camera.h = Game::height;

    // init game entities

    map.LoadMap("assets/lvl2_25x25.map", 25, 25);

    playerEntity.addComponent<TransformComponent>(200, 200, 2);
    playerEntity.addComponent<SpriteComponent>("assets/player_animations.png",
                                               true);
    playerEntity.addComponent<KeyboardController>();
    playerEntity.addComponent<ColliderComponent>("player");
    playerEntity.addGroup(GroupLabel::PlayerGroup);
    playerEntity.addGroup(GroupLabel::CollisionGroup);
  }
}

void Game::update() {
  auto prevPlayerPosition =
      playerEntity.getComponent<TransformComponent>().position;

  enitityManager.refresh();
  enitityManager.update();

  auto &playerTransform = playerEntity.getComponent<TransformComponent>();
  auto &playerCollider = playerEntity.getComponent<ColliderComponent>();

  SDL_Rect tmpRect;
  for (auto &entity : colliders) {
    auto collider = entity->getComponent<ColliderComponent>();
    if (collider.tag != playerCollider.tag &&
        Collision::AABB(playerCollider, collider)) {
      playerTransform.position = prevPlayerPosition;
    }
  }

  Vector2d pPos = playerTransform.position;
  camera.x = pPos.x - camera.w / 2 + playerTransform.scaledWidth() / 2;
  camera.y = pPos.y - camera.h / 2 + playerTransform.scaledHeight() / 2;

  if (camera.x < 0) camera.x = 0;
  if (camera.y < 0) camera.y = 0;
  if (camera.x > (map.width - camera.w)) camera.x = map.width - camera.w;
  if (camera.y > (map.height - camera.h)) camera.y = map.height - camera.h;
}

void Game::handleEvents() { SDL_PollEvent(&event); }

void Game::render() {
  SDL_RenderClear(renderer);
  ///----- main render

  SDL_SetRenderDrawColor(renderer, 130, 230, 60, 255);

  for (auto &tile : tiles) tile->draw();
  for (auto &player : players) player->draw();
  for (auto &collider : colliders) collider->draw();

  /// ------
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "Game cleaned succesfully." << std::endl;
}