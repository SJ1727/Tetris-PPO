#include "engine/TetrisEngine.hpp"

TetrisEngine::TetrisEngine() {
  Init();
}

void TetrisEngine::Init() {
  std::fill(m_Board.begin(), m_Board.end(), NONE);

  m_TotalFrameCount = 0;
  m_Level = 0;
  m_LastMoveDownFrame = 0;

  // Sets used tetrominoes to include one of all possible types
  for (int8_t type; type < NUM_TETROMINO_TYPES; type++) {
    m_UsedTetrominoes.push_back(static_cast<TetrominoType>(type));
  }
  
  // Fills the bag with all the tetromino types randomly
  RefillBag();

  m_HeldTetrominoType = NONE;
  SetCurrentTetrominoToNext();
}

void TetrisEngine::Update() {
  // Moves the current piece based on the next move
  if (m_NextMove != NO_MOVE) {
    AttemptMoveCurrentPiece(m_NextMove);
    m_NextMove = NO_MOVE;
  }

  int speed = m_Level > 19 ? 19 : m_Level;
  // Automatically moves the current tetris piece down
  if (m_TotalFrameCount - m_LastMoveDownFrame >= fallingSpeedLookupTable[speed]) {
    AttemptMoveCurrentPiece(DOWN);
  }

  m_TotalFrameCount += 1;
}

bool TetrisEngine::TetrominoInValidPosition(Tetromino tetromino) {
  if (!tetromino.InBounds(0, BOARD_WIDTH, 0, BOARD_HEIGHT)) { return false; }

  auto blockPositions = tetromino.GetBlockPositions();

  for (auto& blockPosition : blockPositions) {
    if (GetBoardPositionType(blockPosition.x, blockPosition.y) != NONE) {
      return false;
    }
  }

  return true;
}

void TetrisEngine::AttemptMoveCurrentPiece(Move move) {
  Tetromino candidateTetromino;

  if (move == ROTATE_RIGHT || move == ROTATE_LEFT) {
    // Loop through the different tests and uses the super rotation system to find a valid tetromino position
    for (int test = 0; test < NUM_SRS_TESTS; test++) {
      candidateTetromino = m_CurrentTetromino.SrsCandidate(move, test); 

      if (TetrominoInValidPosition(candidateTetromino)) {
        m_CurrentTetromino = candidateTetromino;
        return;
      }
    }

    // If its not possible to find a valid position then do not modify the current tetromino 
    return;
   }

  candidateTetromino = m_CurrentTetromino.Copy();
  
  if (move == DROP) {
    while (TetrominoInValidPosition(candidateTetromino)) {
      m_CurrentTetromino = candidateTetromino;
      candidateTetromino += { 0, 1 };
    }
  }

  switch (move) {
    case RIGHT:
      candidateTetromino += { 1, 0 };
      break;
    case LEFT:
      candidateTetromino += { -1, 0 };
      break;
    case DOWN:
      candidateTetromino += { 0, 1 };
      m_LastMoveDownFrame = m_TotalFrameCount;
      break;
    default:
      return;
  }

  if (TetrominoInValidPosition(candidateTetromino)) {
    m_CurrentTetromino = candidateTetromino;
  }
}

TetrominoType TetrisEngine::GetBoardPositionType(int x, int y) {
  return m_Board[y * BOARD_WIDTH + x];
}

void TetrisEngine::SetBoardPositionType(int x, int y, TetrominoType type) {
  m_Board[y * BOARD_WIDTH + x] = type;
}

std::string TetrisEngine::GetBoardAsString() {
  std::string boardString;
  bool fillIn;

  for (int i = 0; i < BOARD_HEIGHT; i++) {
    boardString += "\n";
    
    // Uses a # to denote a block occupied by a tetromino and a . to denote an empty block
    for (int j = 0; j < BOARD_WIDTH; j++) {
      fillIn = (GetBoardPositionType(j, i) != NONE) || m_CurrentTetromino.Intersects(j, i);
      boardString += fillIn ? "# " : ". ";
    }
  }

  return boardString;
}

void TetrisEngine::PlaceTetromino(Tetromino tetromino) {
  auto blockPositions = tetromino.GetBlockPositions();

  // Sets all cells on the board with same coordinate as a block to the tetromino type
  // It is set to the type instead of just true or false because we want to colour the board
  // Depending on what the tetromino type was
  for (auto& position : blockPositions) {
    SetBoardPositionType(position.x, position.y, tetromino.GetType()); 
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

void TetrisEngine::SetCurrentTetrominoToNext() {
  TetrominoType nextTetrominoType = GetNextTetrominoType();

  m_CurrentTetromino = { nextTetrominoType, ROTATION_0, {BOARD_WIDTH / 2 - 2, 0} };
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

int TetrisEngine::GenerateRandomNumber(int lower, int upper) {
  std::uniform_int_distribution<> dist(lower, upper);
  return dist(m_RandomNumberGen);
}
