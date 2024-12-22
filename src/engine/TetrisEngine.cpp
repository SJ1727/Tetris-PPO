#include "engine/TetrisEngine.hpp"

TetrisEngine::TetrisEngine() {
  std::fill(m_Board.begin(), m_Board.end(), NONE);
  
  for (int8_t type; type < NUMBER_OF_TETROMINO_TYPES; type++) {
    m_UsedTetrominoes.push_back(static_cast<TetrominoType>(type));
  }

  RefillBag();

  for (int i = 0; i < NUMBER_OF_TETROMINO_TYPES; i++) {
    ENGINE_TRACE("{}",(int8_t) m_NextTetrominoBag.front());
    m_NextTetrominoBag.pop();
  }
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
