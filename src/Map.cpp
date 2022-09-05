#include "game/Map.h"

#include <fstream>
#include <iostream>

#include "game/Game.h"

int Map::width = 0;
int Map::height = 0;

constexpr int TILE_SRC_SIZE = 32;
constexpr int TILE_DEST_SIZE = 128;

Map::Map() {}

Map::~Map() {}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
  char tile;
  std::fstream mapFile;
  mapFile.open(path);

  int srcX, srcY;

  Map::width = sizeX * TILE_DEST_SIZE;
  Map::height = sizeY * TILE_DEST_SIZE;

  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      mapFile.get(tile);
      srcY = srcX = atoi(&tile) * TILE_SRC_SIZE;

      mapFile.get(tile);
      if (tile != ',') {
        srcX = atoi(&tile) * TILE_SRC_SIZE;
        mapFile.ignore();
      } else {
        srcY = 0;
      }
      Game::AddTile(srcX, srcY, x * TILE_DEST_SIZE, y * TILE_DEST_SIZE,
                    TILE_SRC_SIZE, TILE_SRC_SIZE, TILE_DEST_SIZE,
                    TILE_DEST_SIZE);  // need to link tile size and position
    }
    mapFile.ignore();
  }

  mapFile.close();
}
