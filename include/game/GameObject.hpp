#ifndef A07F42C2_6FBB_475B_9806_E912B69A98AC
#define A07F42C2_6FBB_475B_9806_E912B69A98AC

#include "game/Game.hpp"

class GameObject
{
public:
    GameObject(const char* texFile, SDL_Renderer *ren, int xpos, int ypos);
    ~GameObject();

    void update();
    void render();

private:
    int xpos;
    int ypos;

    SDL_Texture *texture;
    SDL_Rect src, dest;
    SDL_Renderer *renderer;
};

#endif /* A07F42C2_6FBB_475B_9806_E912B69A98AC */
