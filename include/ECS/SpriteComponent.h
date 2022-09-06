#ifndef BFCCA677_1DAE_48E0_A348_3D0C8D774BAE
#define BFCCA677_1DAE_48E0_A348_3D0C8D774BAE

#include <map>
#include <string>

#include "Animation.h"
#include "Components.h"
#include "SDL2/SDL.h"
#include "ECS/AssetManager.h"
#include "game/TextureManager.h"

class SpriteComponent : public Component {
 private:
  TransformComponent *transform;
  SDL_Texture *texture;
  SDL_Rect src, dest;

  bool animated = false;
  int frames;
  int speed;

 public:
  const std::string IDLE = "idle";
  const std::string WALK = "walk";
  int animIndex = 0;
  std::map<std::string, Animation> animations;
  SDL_RendererFlip flipSprite = SDL_FLIP_NONE;

  SpriteComponent() = default;

  SpriteComponent(const char *path) { setTex(path); }

  SpriteComponent(std::string texID, bool isAnimated = false) {
    animated = isAnimated;
    animations.emplace(IDLE, Animation(0, 4, 200));
    animations.emplace(WALK, Animation(1, 4, 200));
    Play(IDLE);
    setTex(texID);
  }

  ~SpriteComponent() {}

  void init() override {
    transform = &entity->getComponent<TransformComponent>();

    src.x = src.y = 0;
    src.w = transform->width;
    src.h = transform->height;

    dest.w = transform->scaledWidth();
    dest.h = transform->scaledHeight();
  };

  void update() override {
    if (animated) {
      src.x = src.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }

    src.y = animIndex * transform->height;

    dest.x = static_cast<int>(transform->position.x) - Game::camera.x;
    dest.y = static_cast<int>(transform->position.y) - Game::camera.y;
  };

  void draw() override {
    TextureManager::Draw(texture, src, dest, flipSprite);
  };

  void setTex(std::string texID) { texture = Game::assets->GetTexture(texID); }

  void Play(std::string animation) {
    frames = animations[animation].frames;
    animIndex = animations[animation].index;
    speed = animations[animation].speed;
  }
};

#endif /* BFCCA677_1DAE_48E0_A348_3D0C8D774BAE */
