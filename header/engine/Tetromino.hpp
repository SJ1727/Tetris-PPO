#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include "log.hpp"

enum Move:          uint8_t { RIGHT, LEFT, DOWN, ROTATE_LEFT, ROTATE_RIGHT, DROP, HOLD, NO_MOVE };
enum TetrominoType: uint8_t { I, J, L, S, T, Z, O, NONE };
enum Rotation:      uint8_t { ROTATION_0, ROTATION_1, ROTATION_2, ROTATION_3 };

struct Position {
  uint16_t x : 5;
  uint16_t y : 5;
};

Position Add(Position pos1, Position pos2);
Position Subtract(Position pos1, Position pos2);

class Tetromino {
public:
  Tetromino(TetrominoType type, Rotation rotation, Position position);
  ~Tetromino() = default;

  inline Tetromino Copy() { return { m_Type, m_Rotation, m_Position }; }

  inline void operator+(Position offset) { m_Position = Add(m_Position, offset); }
  inline void operator-(Position offset) { m_Position = Add(m_Position, offset); }
  
  inline TetrominoType GetType() { return m_Type; }
  inline Rotation GetRotation()  { return m_Rotation; }
  inline Position GetPosition()  { return m_Position; }

private:
  TetrominoType m_Type; 
  Rotation m_Rotation;
  Position m_Position;
};

constexpr std::array<Position, 100> rotationOffsetLookupTable = {{
  // I piece
  {0, 2}, {1, 2}, {2, 2}, {3, 2},
  {2, 0}, {2, 1}, {2, 2}, {2, 3},
  {0, 1}, {1, 1}, {2, 1}, {3, 1},
  {1, 0}, {1, 1}, {1, 2}, {1, 3},
  // J piece
  {0, 2}, {0, 1}, {1, 1}, {2, 1},
  {1, 2}, {1, 1}, {1, 0}, {2, 2},
  {0, 1}, {1, 1}, {2, 1}, {2, 0},
  {0, 0}, {1, 2}, {1, 1}, {1, 0},
  // L piece
  {0, 1}, {1, 1}, {2, 2}, {2, 1},
  {1, 2}, {1, 1}, {1, 0}, {2, 0},
  {0, 1}, {0, 0}, {1, 1}, {2, 1},
  {0, 2}, {1, 2}, {1, 1}, {1, 0},
  // S piece
  {0, 1}, {1, 2}, {1, 1}, {2, 2},
  {1, 2}, {1, 1}, {2, 1}, {2, 0},
  {0, 0}, {1, 1}, {1, 0}, {2, 1},
  {0, 2}, {0, 1}, {1, 1}, {1, 0},
  // T piece
  {0, 1}, {1, 2}, {1, 1}, {2, 1},
  {1, 2}, {1, 1}, {1, 0}, {2, 1},
  {0, 1}, {1, 1}, {1, 0}, {2, 1},
  {0, 1}, {1, 2}, {1, 1}, {1, 0},
  // Z piece
  {0, 2}, {1, 2}, {1, 1}, {2, 1},
  {1, 1}, {1, 0}, {2, 2}, {2, 1},
  {0, 1}, {1, 1}, {1, 0}, {2, 0},
  {0, 1}, {0, 0}, {1, 2}, {1, 1},
  // O piece
  {0, 1}, {0, 0}, {1, 1}, {1, 0}
}}; 

std::array<Position, 4> GetBlockPositions(Tetromino tetromino);

Tetromino SrsCandidate(Tetromino tetromino, Move rotation, uint8_t test);

#endif // !TETROMINO_H
