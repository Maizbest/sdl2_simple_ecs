#ifndef D0F22BB4_0FE1_46D8_9874_9E5BA116CB41
#define D0F22BB4_0FE1_46D8_9874_9E5BA116CB41

#include "Components.h"
#include "game/Game.h"

class KeyboardController : public Component {
 public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
  };
  void update() override {
    if (Game::event.type == SDL_KEYDOWN) {
      switch (Game::event.key.keysym.sym) {
        case SDLK_w:
          transform->velocity.y = -1.0;
          sprite->Play(sprite->WALK);
          break;
        case SDLK_s:
          transform->velocity.y = 1.0;
          sprite->Play(sprite->WALK);
          break;
        case SDLK_a:
          transform->velocity.x = -1.0;
          sprite->flipSprite = SDL_FLIP_HORIZONTAL;
          sprite->Play(sprite->WALK);
          break;
        case SDLK_d:
          transform->velocity.x = 1.0;
          sprite->Play(sprite->WALK);
          break;
        case SDLK_SPACE:
          Game::assets->CreateProjectile(
              Vector2d(transform->position.x + transform->width * 2,
                       transform->position.y),
              Vector2d(1.0, 0.0), 100, 1, "projectile");
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
          sprite->Play(sprite->IDLE);
          break;
        case SDLK_a:
        case SDLK_d:
          transform->velocity.x = 0.0;
          sprite->flipSprite = SDL_FLIP_NONE;
          sprite->Play(sprite->IDLE);
          break;
        case SDLK_ESCAPE:
          Game::isRunning = false;
        default:
          break;
      }
    };
  };

  void draw() override{};
};

#endif /* D0F22BB4_0FE1_46D8_9874_9E5BA116CB41 */
