#ifndef B4E7E31E_6025_4403_8C57_C327C4F9FB2C
#define B4E7E31E_6025_4403_8C57_C327C4F9FB2C

#include "ECS/Components.h"
#include "SDL2/SDL.h"

class Collision {
 public:
  static bool AABBcollision(SDL_Rect& rectA, SDL_Rect& rectB);
};

#endif /* B4E7E31E_6025_4403_8C57_C327C4F9FB2C */
