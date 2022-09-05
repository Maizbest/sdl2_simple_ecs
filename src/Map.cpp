#include "game/Map.h"

#include <fstream>
#include <iostream>

#include "ECS/Components.h"
#include "ECS/ESC.h"
#include "game/Game.h"

extern Manager enitityManager;

Map::Map(std::string mapFile, int tSize, int tScale)
    : mapFilePath(mapFile), tileScale(tScale), tileSize(tSize) {}

Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
  char c;
  std::fstream mapFile;
  mapFile.open(path);

  int srcX, srcY;

  width = sizeX * tileSize * tileScale;
  height = sizeY * tileSize * tileScale;

  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      mapFile.get(c);
      srcY = srcX = atoi(&c) * tileSize;

      mapFile.get(c);
      if (c != ',') {
        srcX = atoi(&c) * tileSize;
        mapFile.ignore();
      } else {
        srcY = 0;
      }
      AddTile(srcX, srcY, x * tileSize * tileScale, y * tileSize * tileScale,
              tileSize, tileScale);  // need to link tile size and position
    }
    mapFile.ignore();
  }

  mapFile.ignore();

  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      mapFile.get(c);
      // std::cout << c << ' ' << std::endl;
      if (c == '1') {
        auto& collider(enitityManager.addEntity());
        collider.addComponent<ColliderComponent>(
            "terrain", x * tileSize * tileScale, y * tileSize * tileScale,
            tileSize * tileScale);
        collider.addGroup(GroupLabel::CollisionGroup);
      }
      mapFile.ignore();
    }
    // std::cout << std::endl;
    mapFile.ignore();
  }

  mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos, int tSize,
                  int tScale) {
  auto& tile(enitityManager.addEntity());
  tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tSize, tScale,
                                   mapFilePath);
  tile.addGroup(GroupLabel::MapGroup);
}
