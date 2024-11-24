#include "engine/Tetromino.hpp"

Position Add(Position pos1, Position pos2) {
  return { static_cast<uint16_t>(pos1.x + pos2.x), static_cast<uint16_t>(pos1.y + pos2.y) };
}

Position Subtract(Position pos1, Position pos2) {
  return { static_cast<uint16_t>(pos1.x - pos2.x), static_cast<uint16_t>(pos1.y - pos2.y) };
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
      int index = static_cast<int>(tetromino.GetRotation()) * 4 + static_cast<int>(tetromino.getType()) * 16;
      
      return {{
        Add(rotationOffsetLookupTable[index], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[index + 1], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[index + 2], tetromino.GetPosition()),
        Add(rotationOffsetLookupTable[index + 3], tetromino.GetPosition())
      }};
  }; 
}

Tetromino SrsCandidate(Tetromino tetromino, Move rotation, uint8_t test) {
  if (rotation != ROTATE_LEFT && rotation != ROTATE_RIGHT) {
    ENGINE_ERROR("Move must be a rotation");
    return tetromino;
  }

  switch (tetromino.GetType()) {
    case NONE:
      ENGINE_ERROR("Tetromino type should not be none");
      return tetromino;
  }

  return tetromino;
}
