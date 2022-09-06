#include "ECS/AssetManager.h"

#include "ECS/Components.h"

AssetManager::AssetManager(Manager* man) : manager(man) {}

AssetManager::~AssetManager() {}

void AssetManager::AddTexture(std::string id, std::string path) {
  textures.emplace(id, TextureManager::LoadTexture(path.c_str()));
}

SDL_Texture* AssetManager::GetTexture(std::string id) { return textures[id]; }

void AssetManager::CreateProjectile(Vector2d pos, Vector2d velocity, int range,
                                    int speed, std::string texID) {
  auto& projectile(manager->addEntity());
  projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
  projectile.addComponent<SpriteComponent>(texID.c_str());
  projectile.addComponent<ProjectileComponent>(range, speed, velocity);
  projectile.addComponent<ColliderComponent>(texID);
  projectile.addGroup(GroupLabel::ProjectieGroup);
}
