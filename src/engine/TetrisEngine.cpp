#include "engine/TetrisEngine.hpp"

TetrisEngine::TetrisEngine() {
  Init();
}

void TetrisEngine::Init() {
  std::fill(m_Board.begin(), m_Board.end(), NONE);

  m_TotalFrameCount = 0;
  m_Level = 0;
  m_FramesSinceFallen = 0;
  m_FramesSinceMoveDown = 0;
  m_HasHeld = false;

  // Sets used tetrominoes to include one of all possible types
  for (int8_t type; type < NUM_TETROMINO_TYPES; type++) {
    m_UsedTetrominoes.push_back(static_cast<TetrominoType>(type));
  }
  
  // Fills the bag with all the tetromino types randomly
  RefillBag();

  m_HeldTetrominoType = NONE;
  SetCurrentTetrominoByType(GetNextTetrominoType());
}

void TetrisEngine::Update() {
  ENGINE_TRACE("Rotation = {}", (int) m_CurrentTetromino.GetRotation());
  // Moves the current piece based on the next move
  if (m_NextMove != NO_MOVE) {
    AttemptMoveCurrentPiece(m_NextMove);
    m_NextMove = NO_MOVE;
  }

  int speed = m_Level > 19 ? 19 : m_Level;

  // Checks if Tetromino has fallen and if so it gives the next tetromino
  if (CurrentTetrominoHasFallen()) {
    if (m_FramesSinceFallen >= RELATIVE_TIME_UNTIL_LOCK * fallingSpeedLookupTable[speed]) {
      PlaceTetromino(m_CurrentTetromino);
      SetCurrentTetrominoByType(GetNextTetrominoType());
    } else {
      m_FramesSinceFallen++;
    }
  }
  
  // Automatically moves the current tetris piece down
  if (m_FramesSinceMoveDown >= fallingSpeedLookupTable[speed]) {
    AttemptMoveCurrentPiece(DOWN);
  } else {
    m_FramesSinceMoveDown++;
  }

  m_TotalFrameCount++;
}

bool TetrisEngine::TetrominoInValidPosition(Tetromino tetromino) {
  if (!tetromino.InBounds(0, BOARD_WIDTH - 1, 0, BOARD_HEIGHT - 1)) { return false; }

  auto blockPositions = tetromino.GetBlockPositions();

  for (auto& blockPosition : blockPositions) {
    if (GetBoardPositionType(blockPosition.x, blockPosition.y) != NONE) {
      return false;
    }
  }

  return true;
}

bool TetrisEngine::CurrentTetrominoHasFallen() {
  Tetromino testTetromino = m_CurrentTetromino.Copy();
  testTetromino += { 0, 1 };

  return !TetrominoInValidPosition(testTetromino);
}

void TetrisEngine::AttemptMoveCurrentPiece(Move move) {
  Tetromino candidateTetromino;

  if (move == ROTATE_RIGHT || move == ROTATE_LEFT) {
    // Loop through the different tests and uses the super rotation system to find a valid tetromino position
    for (int test = 0; test < NUM_SRS_TESTS; test++) {
      candidateTetromino = m_CurrentTetromino.SrsCandidate(move, test); 

      if (TetrominoInValidPosition(candidateTetromino)) {
        ENGINE_TRACE("Chose candidate from test {}", test);
        m_CurrentTetromino = candidateTetromino;
        return;
      }
    }

    ENGINE_TRACE("Could not find a valid position");

    // If its not possible to find a valid position then do not modify the current tetromino 
    return;
   }

  if (move == HOLD && !m_HasHeld) {
    TetrominoType currentTetrominoType = m_CurrentTetromino.GetType();
    
    // If no piece has been held yet then just set the held type to the current tetromino type and get the next type from the bag
    // Otherwise, swap the held and current tetromino types 
    if (m_HeldTetrominoType == NONE) {
      SetCurrentTetrominoByType(GetNextTetrominoType());
    } else {
      SetCurrentTetrominoByType(m_HeldTetrominoType);
    }
   
    // Used to prevent the player from repeatably holding 
    m_HasHeld = true;

    m_HeldTetrominoType = currentTetrominoType;

    return;
  }

  candidateTetromino = m_CurrentTetromino.Copy();
  
  if (move == DROP) {
    // Keep moving the current piece down until it cant be moved down any further
    while (TetrominoInValidPosition(candidateTetromino)) {
      m_CurrentTetromino = candidateTetromino;
      candidateTetromino += { 0, 1 };
    }
    m_FramesSinceFallen = 1000;
    return;
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
      m_FramesSinceMoveDown = 0;
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
  for (auto& blockPosition : blockPositions) {
    SetBoardPositionType(blockPosition.x, blockPosition.y, tetromino.GetType()); 
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

void TetrisEngine::SetCurrentTetrominoByType(TetrominoType type) {
  m_FramesSinceFallen = 0;
  m_FramesSinceMoveDown = 0;
  
  m_CurrentTetromino = { type, ROTATION_0, {BOARD_WIDTH / 2 - 2, 0} };
}

TetrominoType TetrisEngine::GetNextTetrominoType() {
  // If bag is close to being empty, we need to refill it
  if (m_NextTetrominoBag.size() < NUM_PREVIEW_TETROMINOES + 1) {
    RefillBag();
  }

  // Since we are getting a new tetromino we can now hold
  m_HasHeld = false;
  
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
