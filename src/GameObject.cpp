#include "game/GameObject.h"

#include "game/TextureManager.h"

GameObject::GameObject(const char* texFile, int xpos, int ypos)
    : xpos(xpos),
      ypos(ypos)

{
  texture = TextureManager::LoadTexture(texFile);

  src.x = src.y = 0;
  src.w = src.h = 32;

  dest.x = xpos;
  dest.y = ypos;
  dest.w = dest.h = 64;
}

void GameObject::update() {
  xpos++;
  ypos++;

  dest.x = xpos;
  dest.y = ypos;
}

void GameObject::render() {
  SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

GameObject::~GameObject() {}
