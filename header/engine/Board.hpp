#ifndef BOARD_H
#define BOARD_H

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BOARD_SIZE 200

#include <array>
#include <iostream>
#include "engine/Tetromino.hpp"

class Board {
public:
  Board();
  ~Board() = default;

  int ClearLines();
  void Print(); // For Debugging

private:
  std::array<TetrominoType, BOARD_SIZE> m_Board;
};

#endif // !BOARD_H
