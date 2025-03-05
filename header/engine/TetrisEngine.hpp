#ifndef TETRIS_ENGINE_H
#define TETRIS_ENGINE_H

#include <array>
#include <vector>
#include <queue>
#include <random>
#include <string>
#include <tuple>
#include "engine/Tetromino.hpp"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BOARD_SIZE 200

#define FRAMES_PER_SECOND 50

#define NUM_PREVIEW_TETROMINOES 1

#define RELATIVE_TIME_UNTIL_LOCK 1

#define LINES_PER_LEVEL 10

#define LINE_CLEAR_BONUS 5
#define LINE_HEIGHT_LIMIT 7
#define LINE_HEIGHT_LIMIT_PENALTY 20
#define COVERED_TILE_PENALTY 3
#define TOP_OUT_PENALTY 100

// If the level is greater than 19, use the same speed as level 19
constexpr std::array<int, 20> fallingSpeedLookupTable = { 36, 32, 29, 25, 22, 18, 15, 11, 7, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1 };

class TetrisEngine {
public:
  TetrisEngine();
  ~TetrisEngine() = default;

  void Init();
  void Update();

  static inline int BoardPositionToIndex(int x, int y)      { return y * BOARD_WIDTH + x; }
  static inline int BoardPositionToIndex(Position position) { return position.y * BOARD_WIDTH + position.x; }

  inline void SetNextMove(Move move) { m_NextMove = move; }
  inline void SetLevel(int level)    { m_Level = level; }
  std::string GetBoardAsString();

  std::array<TetrominoType, BOARD_SIZE> GetBoard();
  inline TetrominoType GetBoardPositionType(int x, int y) { return m_Board[BoardPositionToIndex(x, y)]; }
  inline TetrominoType GetHeldTetrominoType()  { return m_HeldTetrominoType; }
  inline TetrominoType PeakNextTetrominoType() { return m_NextTetrominoBag.front(); }
  inline int GetScore()                        { return m_Score; }
  inline int GetLevel()                        { return m_Level; }
  inline int GetLinesCleared()                 { return m_LinesCleared; }

  std::tuple<std::array<int, BOARD_SIZE>, std::array<int, NUM_TETROMINO_TYPES + 1>, float, bool> GetGameState();

private:
  void RefillBag();
  TetrominoType GetNextTetrominoType();
  void SetCurrentTetrominoByType(TetrominoType type);

  inline void SetBoardPositionType(int x, int y, TetrominoType type) { m_Board[BoardPositionToIndex(x, y)] = type; }
  void PlaceTetromino(Tetromino tetromino);

  bool TetrominoInValidPosition(Tetromino tetromino);
  bool CurrentTetrominoHasFallen();
  void AttemptMoveCurrentPiece(Move move);

  void ClearLines();
  int CalculateScore(int lines);

  float CalculateReward();

  int GenerateRandomNumber(int lower, int upper);

private:
  std::array<TetrominoType, BOARD_SIZE> m_Board;
  std::vector<TetrominoType> m_UsedTetrominoes;
  std::queue<TetrominoType> m_NextTetrominoBag;

  Tetromino m_CurrentTetromino;
  TetrominoType m_HeldTetrominoType;
  Move m_NextMove = NO_MOVE;

  int m_TotalFrameCount;
  int m_LinesCleared;
  int m_Score;
  int m_ScoreThisFrame;
  uint8_t m_Level;

  int m_FramesSinceMoveDown;
  int m_FramesSinceFallen;
  bool m_HasHeld;
  bool m_ToppedOut;

  int m_LastFrameLinesOverHeightLimit;
  int m_ThisFrameLinesOverHeightLimit;
  int m_LastFrameCoveredTiles;
  int m_ThisFrameCoveredTiles;

  std::mt19937 m_RandomNumberGen;
};

#endif // !TETRIS_ENGINE_H
