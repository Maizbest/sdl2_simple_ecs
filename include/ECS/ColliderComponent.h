#ifndef AC10B449_5865_4375_B32B_EB8F9952DBB2
#define AC10B449_5865_4375_B32B_EB8F9952DBB2

#include <string>

#include "ECS/Components.h"
#include "SDL2/SDL.h"

class ColliderComponent : public Component {
 public:
  SDL_Rect collider;
  std::string tag;

  TransformComponent *transform;

  ColliderComponent(std::string tag) : tag(tag) {}

  void init() override {
    if (!entity->hasComponents<TransformComponent>()) {
      entity->addComponent<TransformComponent>();
    }

    transform = &entity->getComponent<TransformComponent>();
  }

  void update() override {
    collider.x = static_cast<int>(transform->position.x);
    collider.y = static_cast<int>(transform->position.y);
    collider.w = transform->scaledWidth();
    collider.h = transform->scaledHeight();
  }

  void draw() override {}
};

#endif /* AC10B449_5865_4375_B32B_EB8F9952DBB2 */
