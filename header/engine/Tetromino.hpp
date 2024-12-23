#ifndef TETROMINO_H
#define TETROMINO_H

#include <array>
#include "log.hpp"

#define NUM_TETROMINO_TYPES 7
#define NUM_SRS_TESTS 5

enum Move:          int8_t { RIGHT, LEFT, DOWN, ROTATE_LEFT, ROTATE_RIGHT, DROP, HOLD, NO_MOVE };
enum TetrominoType: int8_t { I, J, L, S, T, Z, O, NONE };
enum Rotation:      int8_t { ROTATION_0, ROTATION_1, ROTATION_2, ROTATION_3 };

struct Position {
  int8_t x;
  int8_t y;
};

Position Add(Position pos1, Position pos2);
Position Subtract(Position pos1, Position pos2);

class Tetromino {
public:
  Tetromino() = default;
  Tetromino(TetrominoType type, Rotation rotation, Position position) 
    : m_Type(type), m_Rotation(rotation), m_Position(position) {}
  ~Tetromino() = default;

  inline Tetromino Copy() { return { m_Type, m_Rotation, m_Position }; }

  inline void operator+=(Position offset) { m_Position = Add(m_Position, offset); }
  inline void operator-=(Position offset) { m_Position = Subtract(m_Position, offset); } 
  
  inline TetrominoType GetType() { return m_Type; }
  inline Rotation GetRotation()  { return m_Rotation; }
  inline Position GetPosition()  { return m_Position; }

  inline void RotateLeft()  { m_Rotation = static_cast<Rotation>((m_Rotation + 3) % 4); }
  inline void RotateRight() { m_Rotation = static_cast<Rotation>((m_Rotation + 1) % 4); }

  Tetromino SrsCandidate(Move rotation, int test);

  bool Intersects(int x, int y);
  inline bool Intersects(Position position) { return Intersects(position.x, position.y); }
  bool InBounds(int8_t minX, int8_t maxX, int8_t minY, int8_t maxY);
  
  std::array<Position, 4> GetBlockPositions();

private:
  TetrominoType m_Type; 
  Rotation m_Rotation;
  Position m_Position;
};

constexpr std::array<Position, 100> rotationOffsetLookupTable = {{
  // I piece
  {0, 1}, {1, 1}, {2, 1}, {3, 1},
  {2, 3}, {2, 2}, {2, 1}, {2, 0},
  {0, 2}, {1, 2}, {2, 2}, {3, 2},
  {1, 3}, {1, 2}, {1, 1}, {1, 0},
  // J piece
  {0, 0}, {0, 1}, {1, 1}, {2, 1},
  {1, 0}, {1, 1}, {1, 2}, {2, 0},
  {0, 1}, {1, 1}, {2, 1}, {2, 2},
  {0, 2}, {1, 0}, {1, 1}, {1, 2},
  // L piece
  {0, 1}, {1, 1}, {2, 0}, {2, 1},
  {1, 0}, {1, 1}, {1, 2}, {2, 2},
  {0, 1}, {0, 2}, {1, 1}, {2, 1},
  {0, 0}, {1, 0}, {1, 1}, {1, 2},
  // S piece
  {1, 0}, {2, 0}, {0, 1}, {1, 1},
  {1, 0}, {1, 1}, {2, 1}, {2, 2},
  {0, 2}, {1, 1}, {1, 2}, {2, 1},
  {0, 0}, {0, 1}, {1, 1}, {1, 2},
  // T piece
  {0, 1}, {1, 0}, {1, 1}, {2, 1},
  {1, 0}, {1, 1}, {1, 2}, {2, 1},
  {0, 1}, {1, 1}, {1, 2}, {2, 1},
  {0, 1}, {1, 0}, {1, 1}, {1, 2},
  // Z piece
  {0, 0}, {1, 0}, {1, 1}, {2, 1},
  {1, 1}, {1, 2}, {2, 0}, {2, 1},
  {0, 1}, {1, 1}, {1, 2}, {2, 2},
  {0, 1}, {0, 2}, {1, 0}, {1, 1},
  // O piece
  {1, 0}, {2, 0}, {1, 1}, {2, 1}
}};

constexpr std::array<Position, 32> srsOffsetLookupTable = {{
  // I piece
  {-2, 0}, {1, 0}, {-2, -1}, {1, 2},
  {-1, 0}, {2, 0}, {-1, 2}, {2, -1},
  {2, 0}, {-1, 0}, {2, 1}, {-1, -2},
  {1, 0}, {-2, 0}, {1, 2}, {-2, 1},
  // Other pieces
  {-1, 0}, {-1, 1}, {0, -2}, {-1, -2},
  {1, 0}, {1, -1}, {0, 2}, {1, 2},
  {1, 0}, {1, 1}, {0, -2}, {1, -2},
  {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}
}};



#endif // !TETROMINO_H
