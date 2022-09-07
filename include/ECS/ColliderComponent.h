#ifndef AC10B449_5865_4375_B32B_EB8F9952DBB2
#define AC10B449_5865_4375_B32B_EB8F9952DBB2

#include <string>

#include "ECS/Components.h"
#include "SDL2/SDL.h"
#include "ECS/TextureManager.h"

class ColliderComponent : public Component {
 public:
  SDL_Rect collider;
  std::string tag;

  SDL_Texture *texture;
  SDL_Rect src, dest;

  TransformComponent *transform;

  ColliderComponent(std::string tag) : tag(tag) {}
  ColliderComponent(std::string tag, int xpos, int ypos, int size) : tag(tag) {
    collider = {xpos, ypos, size, size};
  }

  void init() override {
    if (!entity->hasComponents<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    texture = TextureManager::LoadTexture("assets/collider.png");

    src = {0, 0, 32, 32};
    dest = {collider.x, collider.y, collider.w, collider.h};
  }

  void update() override {
  }

  void draw() override { TextureManager::Draw(texture, src, dest); }
};

#endif /* AC10B449_5865_4375_B32B_EB8F9952DBB2 */
