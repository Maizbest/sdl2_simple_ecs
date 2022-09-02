#include "game/TextureManager.hpp"
#include <string>

std::map<std::string, SDL_Texture*> textures = std::map<std::string, SDL_Texture*>();

SDL_Texture *TextureManager::LoadTexture(const char *fileName, SDL_Renderer *renderer)
{
    if (textures.find(fileName) != textures.end()) {
        std::cout << "Found texture:" << fileName << std::endl;
        return textures[fileName];   
    }

    SDL_Surface *tmpSurface = IMG_Load(fileName);
    SDL_Texture *tex = nullptr;
    if (tmpSurface)
    {
        tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        std::cout << "Texture: " << fileName << " loaded." << std::endl;
        textures[fileName] = tex;
    }
    SDL_FreeSurface(tmpSurface);

    return tex;
}