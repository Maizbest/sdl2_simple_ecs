#include "game/Game.h"

#include <chrono>
#include <string>
#include <vector>

#include "ECS/Collision.h"
#include "ECS/Components.h"
#include "ECS/TextureManager.h"

int Game::width = 800;
int Game::height = 600;

Manager enitityManager;
AssetManager *Game::assets = new AssetManager(&enitityManager);

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

FieldComponent *field = nullptr;

std::chrono::time_point frame_end = std::chrono::high_resolution_clock::now();

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

    assets->AddTexture("cells", "assets/cells.png");
    auto& field = enitityManager.addEntity();
    field.addComponent<KeyboardController>();
    field.addComponent<FieldComponent>(100, 100, 10, 10, "cells");
  }
}

void Game::update() {
  enitityManager.refresh();
  enitityManager.update();
}

void Game::handleEvents() { SDL_PollEvent(&event); }

void Game::render() {
  SDL_RenderClear(renderer);
  ///----- main render

  enitityManager.draw();

  /// ------
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  std::cout << "Game cleaned succesfully." << std::endl;
}