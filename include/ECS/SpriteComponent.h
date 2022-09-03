#ifndef BFCCA677_1DAE_48E0_A348_3D0C8D774BAE
#define BFCCA677_1DAE_48E0_A348_3D0C8D774BAE

#include "Components.h"
#include "SDL2/SDL.h"
#include "game/TextureManager.h"

class SpriteComponent : public Component {
 private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect src, dest;

 public:
  SpriteComponent() = default;
  SpriteComponent(const char *path) { setTex(path); }
  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    src.x = src.y = 0;
    src.w = transform->width;
    src.h = transform->height;

    dest.w = transform->scaledWidth();
    dest.h = transform->scaledHeight();
  };

  void update() override {
    dest.x = static_cast<int>(transform->position.x);
    dest.y = static_cast<int>(transform->position.y);
  };

  void draw() override {
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
  };

  void setTex(const char *path) { texture = TextureManager::LoadTexture(path); }
};

#endif /* BFCCA677_1DAE_48E0_A348_3D0C8D774BAE */
