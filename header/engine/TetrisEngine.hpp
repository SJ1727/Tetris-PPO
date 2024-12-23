#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H

#include <array>
#include <vector>
#include <queue>
#include <random>
#include <string>
#include "engine/Tetromino.hpp"
#include "log.hpp"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BOARD_SIZE 200
#define FRAMES_PER_SECOND 50
#define NUM_PREVIEW_TETROMINOES 1

// If the level is greater than 19, use the same speed as level 19
constexpr std::array<int, 20> fallingSpeedLookupTable = { 36, 32, 29, 25, 22, 18, 15, 11, 7, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1 };

class TetrisEngine {
public:
  TetrisEngine();
  ~TetrisEngine() = default;

  inline TetrominoType GetBoardPositionType(int x, int y);
  std::string GetBoardAsString();

private:
  void RefillBag();
  TetrominoType GetNextTetrominoType();

  int GenerateRandomNumber(int lower, int upper);

private:
  std::array<TetrominoType, BOARD_SIZE> m_Board;
  std::vector<TetrominoType> m_UsedTetrominoes;
  std::queue<TetrominoType> m_NextTetrominoBag;

  Move nextMove = NO_MOVE;

  std::mt19937 m_RandomNumberGen;
};

#endif // !TETRIS_ENGINE_H
