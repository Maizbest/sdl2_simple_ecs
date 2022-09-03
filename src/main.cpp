#include <map>
#include <string>

#include "game/Game.h"

Game* game = nullptr;

int main(int argv, char** args) {
  constexpr uint64_t FRAME_TIME = 1000 / 60;

  std::cout << "main execution" << std::endl;
  game = new Game();
  game->init("Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
             600, false);

  uint64_t frameStart = 0, deltaTime = 0;
  while (game->running()) {
    deltaTime = SDL_GetTicks64() - frameStart;
    
    if (FRAME_TIME < deltaTime) {
      frameStart = SDL_GetTicks64();
      game->handleEvents();
      game->update();
      game->render();
    }
  }

  game->clean();
  system("pause");
  return 0;
}