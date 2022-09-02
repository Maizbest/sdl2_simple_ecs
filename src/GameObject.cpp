#include "game/GameObject.hpp"
#include "game/TextureManager.hpp"

GameObject::GameObject(const char *texFile, SDL_Renderer *ren, int xpos, int ypos) : xpos(xpos), ypos(ypos)

{
    renderer = ren;
    texture = TextureManager::LoadTexture(texFile, ren);

    src.x = src.y = 0;
    src.w = src.h = 32;

    dest.x = xpos;
    dest.y = ypos;
    dest.w = dest.h = 64;
}

void GameObject::update()
{
    xpos++;
    ypos++;

    dest.x = xpos;
    dest.y = ypos;
}

void GameObject::render()
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

GameObject::~GameObject()
{
}
