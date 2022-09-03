#ifndef B71054D1_F895_4119_B74E_78E513C4B66D
#define B71054D1_F895_4119_B74E_78E513C4B66D

#include <map>

#include "Game.h"

enum Terrain { DIRT = 2, GRASS = 1, WATER = 0 };

class Map {
 public:
  Map(/* args */);
  ~Map();
  void LoadMap(int[20][25]);
  void DrawMap();

 private:
  SDL_Rect src, dest;

  static std::map<Terrain, SDL_Texture *> terrains;

  int map[20][25];
};

#endif /* B71054D1_F895_4119_B74E_78E513C4B66D */
