#ifndef BD13B8D7_C105_48E8_AF90_FA2539C26382
#define BD13B8D7_C105_48E8_AF90_FA2539C26382

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

#include "ECS/AssetManager.h"
#include "game/Map.h"

class ColliderComponent;
class AssetManager;

enum GroupLabel : std::size_t {
  MapGroup,
  PlayerGroup,
  EnemyGroup,
  CollisionGroup,
  ProjectieGroup
};

class Game {
 public:
  Game();
  ~Game();

  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);
  void handleEvents();
  void update();
  void render();
  void clean();

  bool running() { return isRunning; };

  static int width;
  static int height;
  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static SDL_Rect camera;
  static AssetManager *assets;

 private:
  SDL_Window *window;
};

#endif /* BD13B8D7_C105_48E8_AF90_FA2539C26382 */
