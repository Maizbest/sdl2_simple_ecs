#ifndef E343C96F_9990_4C4A_90C3_C66EF2C271B8
#define E343C96F_9990_4C4A_90C3_C66EF2C271B8

#include "Game.hpp"
#include <map>

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer *renderer);
};

#endif /* E343C96F_9990_4C4A_90C3_C66EF2C271B8 */
