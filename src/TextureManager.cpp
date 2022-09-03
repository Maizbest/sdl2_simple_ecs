#include "game/TextureManager.h"

#include <string>

std::map<std::string, SDL_Texture *> textures =
    std::map<std::string, SDL_Texture *>();

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
  if (textures.find(fileName) != textures.end()) {
    std::cout << "Found texture:" << fileName << std::endl;
    return textures[fileName];
  }

  SDL_Surface *tmpSurface = IMG_Load(fileName);
  SDL_Texture *tex = nullptr;
  if (tmpSurface) {
    tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    std::cout << "Texture: " << fileName << " loaded." << std::endl;
    textures[fileName] = tex;
  }
  SDL_FreeSurface(tmpSurface);

  return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
  SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}