#ifndef D57E8295_3641_496E_B716_DF48D922D457
#define D57E8295_3641_496E_B716_DF48D922D457

#include "ECS/TileComponent.h"

enum Mark { NONE = 0, FLAG = 1, QUESTION = 2 };

class CellComponent : public Component {
 private:
  TileComponent *tile;
  bool isOpen = false;
  Mark mark = NONE;
  bool hasMine = false;
  short bombsAround = 0;
  int m_size;

 public:
  CellComponent(bool mined, int bombsAround, int size = 32)
      : hasMine(mined), bombsAround(bombsAround), m_size(size){};
  ~CellComponent(){};

  void marked() {
    if (!isOpen) {
      mark = static_cast<Mark>((static_cast<int>(mark) + 1) % 3);
      std::cout << "Next Mark: " << mark << std::endl;

      tile->src.y = m_size * 1;
      tile->src.x = m_size * mark;
    }
  };

  void open() {
    isOpen = true;
    if (!hasMine) {
      tile->src.y = bombsAround > 0 ? 0 : m_size;
      tile->src.x = bombsAround > 0 ? m_size * (bombsAround - 1) : m_size * 4;
    } else {
      tile->src.y = m_size * 1;
      tile->src.x = m_size * 3;
    }
  }

  void update() override{};
  void draw() override{};
  void init() override {
    tile = &entity->getComponent<TileComponent>();
    tile->src.x = 0;
    tile->src.y = 1 * m_size;
  };
};

#endif /* D57E8295_3641_496E_B716_DF48D922D457 */
