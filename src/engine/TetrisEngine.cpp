#include "engine/TetrisEngine.hpp"

TetrisEngine::TetrisEngine() {
  std::fill(m_Board.begin(), m_Board.end(), NONE);
  
  for (int8_t type; type < NUM_TETROMINO_TYPES; type++) {
    m_UsedTetrominoes.push_back(static_cast<TetrominoType>(type));
  }

  RefillBag();

  for (int i = 0; i < NUM_TETROMINO_TYPES; i++) {
    ENGINE_TRACE("{}",(int8_t) m_NextTetrominoBag.front());
    m_NextTetrominoBag.pop();
  }
}

TetrominoType TetrisEngine::GetBoardPositionType(int x, int y) {
  return m_Board[y * BOARD_WIDTH + x];
}

std::string TetrisEngine::GetBoardAsString() {
  std::string boardString;

  for (int i = 0; i < BOARD_HEIGHT; i++) {
    boardString += "\n";
    
    for (int j = 0; j < BOARD_WIDTH; j++) {
      boardString += std::to_string(7 - GetBoardPositionType(j, i)) + " ";
    }
  }

  return boardString;
}

void TetrisEngine::RefillBag() {
  int index;
  int size = m_UsedTetrominoes.size();

  // Uses the Fisher-Yates algorithm to randomly add tetrominoes to the bag
  for (int i = 0; i < size; i++) {
    index = GenerateRandomNumber(0, size - i - 1);
    m_NextTetrominoBag.push(m_UsedTetrominoes[index]);
    m_UsedTetrominoes.erase(m_UsedTetrominoes.begin() + index);
  }
}

int TetrisEngine::GenerateRandomNumber(int lower, int upper) {
  std::uniform_int_distribution<> dist(lower, upper);
  return dist(m_RandomNumberGen);
}

TetrominoType TetrisEngine::GetNextTetrominoType() {
  // If bag is close to being empty, we need to refill it
  if (m_NextTetrominoBag.size() < NUM_PREVIEW_TETROMINOES + 1) {
    RefillBag();
  }

  // Gets next tetromino type
  TetrominoType nextType = m_NextTetrominoBag.front();
  
  m_UsedTetrominoes.push_back(nextType);

  // Removes piece from the bag
  m_NextTetrominoBag.pop();

  return nextType;
}
