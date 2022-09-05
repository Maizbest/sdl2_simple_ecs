#ifndef B71054D1_F895_4119_B74E_78E513C4B66D
#define B71054D1_F895_4119_B74E_78E513C4B66D

#include <map>
#include <string>

class Map {
 public:
  Map(std::string mapFile, int tSize, int tScale);
  ~Map();

  int width;
  int height;

  // methods
  void LoadMap(std::string path, int sizeX, int sizeY);
  void AddTile(int srcX, int srcY, int xpos, int ypos, int tSize, int tScale);

 private:
  std::string mapFilePath;
  int tileSize;
  int tileScale;
};

#endif /* B71054D1_F895_4119_B74E_78E513C4B66D */
