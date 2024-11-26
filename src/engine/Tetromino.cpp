#include "engine/Tetromino.hpp"

Position Add(Position pos1, Position pos2) {
  return { static_cast<int8_t>(pos1.x + pos2.x), static_cast<int8_t>(pos1.y + pos2.y) };
}

Position Subtract(Position pos1, Position pos2) {
  return { static_cast<int8_t>(pos1.x - pos2.x), static_cast<int8_t>(pos1.y - pos2.y) };
}

std::array<Position, 4> GetBlockPositions(Tetromino tetromino) {
  switch (tetromino.GetType()) {
    case NONE:
      ENGINE_ERROR("Tetromino type should not be none");
      return {{ {0, 0}, {0, 0}, {0, 0}, {0, 0} }};

    case O:
      return {{
        Add(rotationOffsetLookupTable[96], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[97], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[98], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[99], tetromino.GetPosition())
      }};

    default:
      int index = static_cast<int>(tetromino.GetRotation()) * 4 + static_cast<int>(tetromino.GetType()) * 16;
      
      return {{
        Add(rotationOffsetLookupTable[index], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[index + 1], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[index + 2], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[index + 3], tetromino.GetPosition())
      }};
  }; 
}

Tetromino SrsCandidate(Tetromino tetromino, Move rotation, int test) {
  if (rotation != ROTATE_LEFT && rotation != ROTATE_RIGHT) {
    ENGINE_ERROR("Move must be a rotation");
    return tetromino;
  }

  if (test > 4) {
    ENGINE_ERROR("Test number must be in the range 0-4 inclusive");
    return tetromino;
  }

  // Case where there should be no rotation, no need to lookup
  if (test == 0 || tetromino.GetType() == O) {
    return tetromino;
  }

  Position offset;
  int index = static_cast<int>(tetromino.GetRotation()) * 4 + (test - 1);

  // Getting the offset from the lookup table
  switch (tetromino.GetType()) {
    case NONE:
      ENGINE_ERROR("Tetromino type should not be none");
      return tetromino;
    case I:
      offset = srsOffsetLookupTable[index];
      break;
    default:
      offset = srsOffsetLookupTable[index + 16];
      break;
  }

  // If the rotation is anti clockwise we need to subtract the offset rather than add it
  if (rotation == ROTATE_LEFT) {
    tetromino -= offset;
  } else {
    tetromino += offset;
  }

  return tetromino;
}
