#include "engine/Tetromino.hpp"

bool Tetromino::Intersects(int x, int y) {
  auto blockPositions = GetBlockPositions();

  // Loops through all the block position and check if coordinates are the same
  for (auto& blockPosition : blockPositions) {
    if (blockPosition.x == x && blockPosition.y == y) {
      return true;
    }
  }

  return false;
}


bool Tetromino::InBounds(int8_t minX, int8_t maxX, int8_t minY, int8_t maxY) {
  auto blockPositions = GetBlockPositions();

  for (auto& blockPosition : blockPositions) {
    if (blockPosition.x < minX && blockPosition.x > maxX && blockPosition.y < minY && blockPosition.y > maxY) {
      return false;
    }
  }

  return true;
}

Position Add(Position pos1, Position pos2) {
  return { static_cast<int8_t>(pos1.x + pos2.x), static_cast<int8_t>(pos1.y + pos2.y) };
}

Position Subtract(Position pos1, Position pos2) {
  return { static_cast<int8_t>(pos1.x - pos2.x), static_cast<int8_t>(pos1.y - pos2.y) };
}

std::array<Position, 4> Tetromino::GetBlockPositions() {
  switch (m_Type) {
    case NONE:
      return {{ {0, 0}, {0, 0}, {0, 0}, {0, 0} }};

    case O:
      return {{
        Add(rotationOffsetLookupTable[96], m_Position),
        Add(rotationOffsetLookupTable[97], m_Position),
        Add(rotationOffsetLookupTable[98], m_Position),
        Add(rotationOffsetLookupTable[99], m_Position)
      }};

    default:
      int index = static_cast<int>(m_Rotation) * 4 + static_cast<int>(m_Type) * 16;
      
      return {{
        Add(rotationOffsetLookupTable[index    ], m_Position),
        Add(rotationOffsetLookupTable[index + 1], m_Position),
        Add(rotationOffsetLookupTable[index + 2], m_Position),
        Add(rotationOffsetLookupTable[index + 3], m_Position)
    }};
  };
}

Tetromino Tetromino::SrsCandidate(Move rotation, int test) {
  Tetromino candidate = Copy();

  if (rotation != ROTATE_LEFT && rotation != ROTATE_RIGHT) {
    return candidate;
  }

  if (test > 4) {
    return candidate;
  }

  // Case where there should be no rotation, no need to lookup
  if (test == 0 || m_Type == O) {
    return candidate;
  }

  Position offset;
  int index = static_cast<int>(m_Rotation) * 4 + (test - 1);

  // Getting the offset from the lookup table
  switch (m_Type) {
    case NONE:
      return candidate;
    case I:
      offset = srsOffsetLookupTable[index];
      break;
    default:
      offset = srsOffsetLookupTable[index + 16];
      break;
  }

  // If the rotation is anti clockwise we need to subtract the offset rather than add it
  if (rotation == ROTATE_LEFT) {
    candidate.RotateLeft();
    candidate -= offset; 
  } else {
    candidate.RotateRight();
    candidate += offset;
  }

  return candidate;
}
