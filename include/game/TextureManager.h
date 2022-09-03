#ifndef E343C96F_9990_4C4A_90C3_C66EF2C271B8
#define E343C96F_9990_4C4A_90C3_C66EF2C271B8

#include <map>

#include "Game.h"

class TextureManager
{
  public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#endif /* E343C96F_9990_4C4A_90C3_C66EF2C271B8 */
