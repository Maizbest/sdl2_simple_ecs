#ifndef D32DA645_0FCF_452D_8F1E_5C639491CC5F
#define D32DA645_0FCF_452D_8F1E_5C639491CC5F

#include <stdlib.h>

#include <array>
#include <string>
#include <vector>

#include "ECS/AssetManager.h"
#include "ECS/Components.h"
#include "game/Game.h"

extern Manager enitityManager;

class FieldComponent : public Component {
 private:
  int m_xpos, m_ypos;
  int m_cols, m_rows;
  std::string m_textureID;
  std::vector<Entity*> cells;
  int cellScale = 1;
  int cellSize = 32;
  std::array<int, 8> shifts;
  int bombAmount;

  int getCellIndex(const int& xpos, const int& ypos) {
    if (xpos < m_xpos || ypos < m_ypos || xpos > m_xpos + m_cols * cellSize ||
        ypos > m_ypos + m_rows * cellSize) {
      return -1;
    }
    int col = (xpos - m_xpos) / cellSize, row = (ypos - m_ypos) / cellSize;
    std::cout << "Relative click: " << row << ' ' << col << std::endl;
    return row * m_cols + col;
  }

  void openCell(int index) {
    if (index >= 0 && index < cells.size()) {
      auto& cell = cells.at(index)->getComponent<CellComponent>();

      if (!cell.isOpen()) {
        cell.open();
        if (cell.isEmpty()) {
          for (int shift : shifts) {
            int nextIndex = index + shift;
            if (nextIndex >= 0 && nextIndex < m_cols * m_rows &&
                (nextIndex % m_cols == (index % m_cols) ||
                 nextIndex % m_cols == (index % m_cols) - 1 ||
                 nextIndex % m_cols == (index % m_cols) + 1)) {
              openCell(nextIndex);
            }
          }
        }
      }
    }
  }

  inline int cellIndex(int row, int col) { return row * m_cols + col; }

 public:
  FieldComponent(int xpos, int ypos, int columns, int rows,
                 std::string textureID)
      : m_textureID(textureID),
        m_xpos(xpos),
        m_ypos(ypos),
        m_cols(columns),
        m_rows(rows) {
    shifts = {-m_cols - 1, -m_cols,    -m_cols + 1, -1,
              1,           m_cols - 1, m_cols,      m_cols + 1};
    bombAmount = (m_cols * m_rows) / 5;
    
    srand(time(NULL));
    std::vector<int> cellValues(m_cols * m_rows, 0);

    for (int i = 0, x = 0, y = 0, index = 0; i < bombAmount; i++) {
      do {
        x = rand() % m_cols, y = rand() % m_rows;
        index = cellIndex(y, x);
      } while (cellValues[index] == -1);
      std::cout << "Bomb at row: " << y << ", col: " << x << std::endl;
      cellValues[index] = -1;
    }

    for (int i = 0; i < cellValues.size(); i++) {
      if (cellValues[i] == -1) {
        for (int shift : shifts) {
          int nextIndex = i + shift;
          if (nextIndex >= 0 && nextIndex < m_cols * m_rows &&
              cellValues[nextIndex] != -1 &&
              (nextIndex % m_cols == (i % m_cols) ||
               nextIndex % m_cols == (i % m_cols) - 1 ||
               nextIndex % m_cols == (i % m_cols) + 1)) {
            cellValues[nextIndex] += 1;
          }
        }
      }
    }

    for (int i = 0; i < cellValues.size(); i++) {
      AddCell(0, 0, xpos + (i % m_cols) * cellSize * cellScale,
              ypos + (i / m_cols) * cellSize * cellScale, cellValues[i] == -1,
              cellValues[i]);
    }
  }

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

  void handleMouseLeftDown(int xpos, int ypos) {
    auto cellIndex = getCellIndex(xpos, ypos);
    if (cellIndex != -1) {
      if (cells[cellIndex]->getComponent<CellComponent>().hasMine()) {
        std::cout << "GAME OVER." << std::endl;
        for (auto& cell : cells) {
          cell->getComponent<CellComponent>().open();
        }
      } else {
        openCell(cellIndex);
      }
    }
  }

  void handleMouseLeftUp(int xpos, int ypos) {}

  void handleMouseLeftAndRightDown(int xpos, int ypos) {
    // auto cell = getCellByCoord(xpos, ypos);
    // if (cell) {
    //   cell->getComponent<CellComponent>().open();
    // }
  }

  void handleRightClick(int xpos, int ypos) {
    int index = getCellIndex(xpos, ypos);
    if (index != -1) {
      cells.at(index)->getComponent<CellComponent>().marked();
    }
  }

  void init() override {}
  void update() override {
    int countOpen = 0;
    for (int i = 0; i < cells.size(); i++)
    {
      countOpen += cells[i]->getComponent<CellComponent>().isOpen() ? 1 : 0;
    }

    if (countOpen == cells.size() - bombAmount) {
      std::cout << "YOU WIN!!!" << std::endl;
    }
  }
  void draw() override {}
};

#endif /* D32DA645_0FCF_452D_8F1E_5C639491CC5F */
