#ifndef D0F22BB4_0FE1_46D8_9874_9E5BA116CB41
#define D0F22BB4_0FE1_46D8_9874_9E5BA116CB41

#include "ECS/FieldComponent.h"
#include "game/Game.h"

extern Manager enitityManager;

class KeyboardController : public Component {
 public:
  void init() override{};
  void update() override {
    if (Game::event.type == SDL_KEYDOWN) {
      switch (Game::event.key.keysym.sym) {
        default:
          break;
      }
    }
    if (Game::event.type == SDL_KEYUP) {
      switch (Game::event.key.keysym.sym) {
        case SDLK_ESCAPE:
          Game::isRunning = false;
        default:
          break;
      }
    };

    if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
      int xpos, ypos;
      SDL_GetMouseState(&xpos, &ypos);
      std::cout << "click: " << xpos << ' ' << ypos << std::endl;
      if (Game::event.button.button == SDL_BUTTON_LEFT) {
        entity->getComponent<FieldComponent>().leftClick(xpos, ypos);
      }

      if (Game::event.button.button == SDL_BUTTON_RIGHT) {
        entity->getComponent<FieldComponent>().rightClick(xpos, ypos);
      }
    }
    if (Game::event.type == SDL_MOUSEBUTTONUP) {
    }
  };

  void draw() override{};
};

#endif /* D0F22BB4_0FE1_46D8_9874_9E5BA116CB41 */
