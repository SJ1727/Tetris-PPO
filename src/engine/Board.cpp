#include "engine/Board.hpp"

Board::Board() {
  std::fill(m_Board.begin(), m_Board.end(), NONE);
}

void Board::Print() {
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      std::cout << static_cast<int>(m_Board[i + j * BOARD_HEIGHT]) << " ";
    }
    std::cout << "\n";
  }
}
