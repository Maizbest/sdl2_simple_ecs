#ifndef D0F22BB4_0FE1_46D8_9874_9E5BA116CB41
#define D0F22BB4_0FE1_46D8_9874_9E5BA116CB41

#include "Components.h"
#include "game/Game.h"

class KeyboardController : public Component {
 public:
  TransformComponent *transform;

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
  };
  void update() override {
    if (Game::event.type == SDL_KEYDOWN) {
      switch (Game::event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = -1.0;
          break;
        case SDLK_s:
          transform->velocity.y = 1.0;
          break;
        case SDLK_a:
          transform->velocity.x = -1.0;
          break;
        case SDLK_d:
          transform->velocity.x = 1.0;
          break;
        default:
          break;
      }
      std::cout << transform->velocity << std::endl;
    }
    if (Game::event.type == SDL_KEYUP) {
      switch (Game::event.key.keysym.sym) {
        case SDLK_w:
        case SDLK_s:
          transform->velocity.y = 0.0;
          break;
        case SDLK_a:
        case SDLK_d:
          transform->velocity.x = 0.0;
          break;
        default:
          break;
      }
    };
  };

  void draw() override{};
};

#endif /* D0F22BB4_0FE1_46D8_9874_9E5BA116CB41 */
