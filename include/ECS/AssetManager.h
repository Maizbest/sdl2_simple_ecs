#ifndef CD4D61B5_6E0E_4BF4_AB9E_8716CE54C17F
#define CD4D61B5_6E0E_4BF4_AB9E_8716CE54C17F

#include <map>
#include <string>

#include "ECS/ESC.h"
#include "ECS/TextureManager.h"
#include "game/Vector2d.h"

class AssetManager {
 public:
  AssetManager(Manager *man);
  ~AssetManager();
  // object management
  void CreateProjectile(Vector2d pos, Vector2d velocity, int range, int speed,
                        std::string texID);

  // texture management
  void AddTexture(std::string id, std::string path);
  SDL_Texture *GetTexture(std::string id);

 private:
  Manager *manager;
  std::map<std::string, SDL_Texture *> textures;
};

#endif /* CD4D61B5_6E0E_4BF4_AB9E_8716CE54C17F */
