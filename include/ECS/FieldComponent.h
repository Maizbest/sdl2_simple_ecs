#ifndef D32DA645_0FCF_452D_8F1E_5C639491CC5F
#define D32DA645_0FCF_452D_8F1E_5C639491CC5F

#include <string>
#include <vector>
#include <stdlib.h>

#include "ECS/AssetManager.h"
#include "ECS/Components.h"

extern Manager enitityManager;

class FieldComponent : public Component {
 private:
  int m_xpos, m_ypos;
  int m_cols, m_rows;
  std::string m_textureID;
  std::vector<Entity*> cells;
  int cellScale = 1;
  int cellSize = 32;

  Entity* getCellByCoord(const int& xpos, const int& ypos) {
    if (xpos < m_xpos || ypos < m_ypos || xpos > m_xpos + m_cols * cellSize ||
        ypos > m_ypos + m_rows * cellSize) {
      return nullptr;
    }
    int col = (xpos - m_xpos) / cellSize, row = (ypos - m_ypos) / cellSize;
    std::cout << "Relative click: " << row << ' ' << col << std::endl;
    return cells.at(row * m_cols + col);
  }

 public:
  FieldComponent(int xpos, int ypos, int columns, int rows,
                 std::string textureID)
      : m_textureID(textureID),
        m_xpos(xpos),
        m_ypos(ypos),
        m_cols(columns),
        m_rows(rows) {


    srand(time(NULL));
    for (int row = 0; row < rows; row++) {
      for (int col = 0; col < columns; col++) {
        AddCell(0, 0, xpos + col * cellSize * cellScale,
                ypos + row * cellSize * cellScale, rand() % 1, rand() % 8);
      }
    }
  };
  ~FieldComponent(){};

  void AddCell(int srcX, int srcY, int xpos, int ypos, bool mined,
               int bombsAround) {
    auto& cell(enitityManager.addEntity());
    cell.addComponent<TileComponent>(srcX, srcY, xpos, ypos, cellSize,
                                     cellScale, m_textureID);
    cell.addComponent<CellComponent>(mined, bombsAround);
    cell.addGroup(GroupLabel::MapGroup);
    cells.emplace_back(&cell);
  }

  void leftClick(int xpos, int ypos) {
    auto cell = getCellByCoord(xpos, ypos);
    if (cell) {
      cell->getComponent<CellComponent>().open();
    }
  }

  void rightClick(int xpos, int ypos) {
    auto cell = getCellByCoord(xpos, ypos);
    if (cell) {
      cell->getComponent<CellComponent>().marked();
    }
  }

  void init() override {}
  void update() override {}
  void draw() override {}
};

#endif /* D32DA645_0FCF_452D_8F1E_5C639491CC5F */
