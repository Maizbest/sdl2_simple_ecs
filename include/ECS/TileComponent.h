#ifndef E39F01FC_CA2F_4640_BE7A_64E9CCF59BBA
#define E39F01FC_CA2F_4640_BE7A_64E9CCF59BBA

#include <string>

#include "ECS/Components.h"
#include "SDL2/SDL.h"
#include "game/Map.h"

class TileComponent : public Component {
 public:
  SDL_Texture *texture;
  SDL_Rect src, dest;
  Vector2d position;

  TileComponent() = default;

  ~TileComponent() { SDL_DestroyTexture(texture); };

  TileComponent(int srcX, int srcY, int xpos, int ypos, int sourceW,
                int sourceH, int destW, int destH, std::string path) {
    texture = TextureManager::LoadTexture(path.c_str());

    position.x = xpos;
    position.y = ypos;

    src.x = srcX;
    src.y = srcY;
    src.w = sourceW;
    src.h = sourceH;

    dest.x = xpos;
    dest.y = ypos;
    dest.w = destW;
    dest.h = destH;
  }

  void init() override{};

  void draw() override { TextureManager::Draw(texture, src, dest); };

  void update() override {
    dest.x = position.x - Game::camera.x;
    dest.y = position.y - Game::camera.y;
  };
};

#endif /* E39F01FC_CA2F_4640_BE7A_64E9CCF59BBA */