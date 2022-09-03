#ifndef AF083087_D7AB_424C_879D_04E094856244
#define AF083087_D7AB_424C_879D_04E094856244

#include "Components.h"
#include "game/Vector2d.h"

class TransformComponent : public Component {
 public:
  Vector2d position;
  Vector2d velocity;
  float speed = 3.0;

  TransformComponent() : position(Vector2d(0.0, 0.0)) {}

  TransformComponent(float x, float y) : position(Vector2d(x, y)) {}

  void init() override {
    velocity.x = 0.0;
    velocity.y = 0.0;
  }

  void update() override {
    position.Add(velocity * speed);
  }

  void draw() override{};
};

#endif /* AF083087_D7AB_424C_879D_04E094856244 */
