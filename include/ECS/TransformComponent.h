#ifndef AF083087_D7AB_424C_879D_04E094856244
#define AF083087_D7AB_424C_879D_04E094856244

#include "Components.h"
#include "game/Vector2d.h"

class TransformComponent : public Component {
 public:
  Vector2d position = Vector2d(0.0, 0.0);
  Vector2d velocity = Vector2d(0.0, 0.0);

  int width = 32;
  int height = 32;
  float scale = 1.0;
  float speed = 3.0;

  TransformComponent() : position(Vector2d(0.0, 0.0)) {}
  TransformComponent(int scale) : scale(scale) {}

  TransformComponent(float x, float y) : position(Vector2d(x, y)) {}
  TransformComponent(float x, float y, int w, int h, int scale)
      : position(Vector2d(x, y)), width(w), height(h), scale(scale) {}

  void init() override {
    velocity.x = 0.0;
    velocity.y = 0.0;
  }

  void update() override { position.Add(velocity * speed); }

  void draw() override{};

  int scaledWidth() const { return width * scale; };
  int scaledHeight() const { return height * scale; };
};

#endif /* AF083087_D7AB_424C_879D_04E094856244 */
