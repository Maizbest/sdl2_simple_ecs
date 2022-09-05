#ifndef B71054D1_F895_4119_B74E_78E513C4B66D
#define B71054D1_F895_4119_B74E_78E513C4B66D

#include <map>
#include <string>

class Map {
 public:
  Map();
  ~Map();



  static int width;
  static int height;
  // methods
  static void LoadMap(std::string path, int sizeX, int sizeY);
};

#endif /* B71054D1_F895_4119_B74E_78E513C4B66D */
