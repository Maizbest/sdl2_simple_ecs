#ifndef AF083087_D7AB_424C_879D_04E094856244
#define AF083087_D7AB_424C_879D_04E094856244

#include "Components.h"
#include "game/Vector2d.h"

class TransformComponent : public Component {
 public:
  Vector2d position;
  Vector2d velocity;

  int width = 32;
  int height = 32;
  float scale = 1.0;
  float speed = 3.0;

  TransformComponent() { position.Zero(); }

  TransformComponent(int scale) : scale(scale) { setPos(400, 300); }

  TransformComponent(float x, float y) { setPos(x, y); }

  TransformComponent(float x, float y, int scale) : scale(scale) { setPos(x, y); }

  TransformComponent(float x, float y, int w, int h, int scale)
      : width(w), height(h), scale(scale) {
    setPos(x, y);
  }

  void init() override { velocity.Zero(); }

  void update() override {
    position.Add(velocity * speed);
  }

  void draw() override{};

  int scaledWidth() const { return width * scale; };
  int scaledHeight() const { return height * scale; };

  void setPos(float x, float y) {
    position.x = x;
    position.y = y;
  }
};

#endif /* AF083087_D7AB_424C_879D_04E094856244 */
