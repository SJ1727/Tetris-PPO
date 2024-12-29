#include "engine/TetrisEngine.hpp"

TetrisEngine::TetrisEngine() {
  Init();
}



void TetrisEngine::Init() {
  std::fill(m_Board.begin(), m_Board.end(), NONE);

  m_TotalFrameCount = 0;
  m_LinesCleared = 0;
  m_Score = 0;
  m_ScoreThisFrame = 0;
  m_Level = 0;
  m_FramesSinceFallen = 0;
  m_FramesSinceMoveDown = 0;
  m_HasHeld = false;
  m_ToppedOut = false;
  m_LastFrameLinesOverHeightLimit = 0;
  m_ThisFrameLinesOverHeightLimit = 0;
  m_LastFrameCoveredTiles = 0;
  m_ThisFrameCoveredTiles = 0;

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
  if (m_ToppedOut) { return; }

  m_ScoreThisFrame = 0;

  // Moves the current piece based on the next move
  if (m_NextMove != NO_MOVE) {
    AttemptMoveCurrentPiece(m_NextMove);
    m_NextMove = NO_MOVE;
  }

  int speed = m_Level > 19 ? 19 : m_Level;
  
  // Automatically moves the current tetris piece down
  if (m_FramesSinceMoveDown >= fallingSpeedLookupTable[speed]) {
    AttemptMoveCurrentPiece(DOWN);
  } else {
    m_FramesSinceMoveDown++;
  }

  // Checks if Tetromino has fallen and if so it gives the next tetromino
  if (CurrentTetrominoHasFallen()) {
    if (m_FramesSinceFallen >= RELATIVE_TIME_UNTIL_LOCK * fallingSpeedLookupTable[speed]) {
      PlaceTetromino(m_CurrentTetromino);
      SetCurrentTetrominoByType(GetNextTetrominoType());
    } else {
      m_FramesSinceFallen++;
    }

    ClearLines();
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
        m_CurrentTetromino = candidateTetromino;
        return;
      }
    }

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
    m_FramesSinceFallen = 1000; // Bit of a hack
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



void TetrisEngine::ClearLines() {
  int linesCleared = 0;
  bool lineIsFull;

  // Loops through the rows starting from the bottom
  for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
    lineIsFull = true;

    // Checks if lines is full
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (GetBoardPositionType(j, i) == NONE) {
        lineIsFull = false;
        break;
      }
    }

    // If lines is full we add one to the number of lines cleared and then go back to the top of the loop
    if (lineIsFull) {
      linesCleared++;
      continue;
    }

    // If the line is not full we move it down by the number of lines cleared
    for (int j = 0; j < BOARD_WIDTH; j++) {
      SetBoardPositionType(j, i + linesCleared, GetBoardPositionType(j, i));
    }
  }

  m_LinesCleared += linesCleared;

  m_ScoreThisFrame = CalculateScore(linesCleared);
  m_Score += m_ScoreThisFrame;
}



int TetrisEngine::CalculateScore(int linesCleared) {
  switch (linesCleared) {
    case 4:
      return 800 * (m_Level + 1);
    case 3:
      return 500 * (m_Level + 1);
    case 2:
      return 300 * (m_Level + 1);
    case 1:
      return 100 * (m_Level + 1);
    default:
      return 0;
  }
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



std::array<TetrominoType, BOARD_SIZE> TetrisEngine::GetBoard() {
  std::array<TetrominoType, BOARD_SIZE> board = m_Board;

  // Place the current tetromino onto the board to be returned
  auto blockPositions = m_CurrentTetromino.GetBlockPositions();
  for (auto& blockPosition : blockPositions) {
    board[BoardPositionToIndex(blockPosition)] = m_CurrentTetromino.GetType();
  }

  return board;
}



std::tuple<std::array<int, BOARD_SIZE>, std::array<int, NUM_TETROMINO_TYPES + 1>, float, bool> TetrisEngine::GetGameState() {
  std::array<int, BOARD_SIZE> board;
  std::array<int, NUM_TETROMINO_TYPES + 1> heldPiece;
  float reward;

  // One hot encoding for the held tetromino
  std::fill(heldPiece.begin(), heldPiece.end(), 0);
  heldPiece[m_HeldTetrominoType] = 1;

  // Sets the filled position with 1 and unfilled with 0
  for (int i = 0; i < BOARD_SIZE; i++) {
    board[i] = m_Board[i] == NONE ? 0 : 1;
  }

  // Setting the positions of the board occupied by the current tetromino by -1
  auto blockPositions = m_CurrentTetromino.GetBlockPositions();
  for (auto& blockPosition : blockPositions) {
    board[BoardPositionToIndex(blockPosition)] = -1;
  }

  reward = CalculateReward();

  return std::make_tuple(board, heldPiece, reward, m_ToppedOut);
}



float TetrisEngine::CalculateReward() {
  float reward = 0;
  bool aboveHeightLimit = false;
  bool foundOccupiedTile;

  // Gaining score will increase the amount of reward given
  // I divide by the current level because i dont want the reward to be dependent on the
  // current level 
  reward += m_ScoreThisFrame / (m_Level + 1) * LINE_CLEAR_BONUS;

  m_LastFrameLinesOverHeightLimit = m_ThisFrameLinesOverHeightLimit;
  m_ThisFrameLinesOverHeightLimit = 0;

  // If there are tetrominoes placed above the defined height limit then a negative reward
  // is given to discourage the policy fron choosing actions that increase the height
  for (int i = 0; i < BOARD_HEIGHT - LINE_HEIGHT_LIMIT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      if (GetBoardPositionType(j, i) != NONE) {
        aboveHeightLimit = true;
        m_ThisFrameLinesOverHeightLimit = (BOARD_HEIGHT - LINE_HEIGHT_LIMIT - i);
        break;
      }
    }

    if (aboveHeightLimit) { break; }
  }

  m_LastFrameCoveredTiles = m_ThisFrameCoveredTiles;
  m_ThisFrameCoveredTiles = 0;

  // Goes column by column and counts number of unoccupied tile covered by an occupied tile
  for (int i = 0; i < BOARD_WIDTH; i++) {
    foundOccupiedTile = false;

    for (int j = 0; j < BOARD_HEIGHT; j++) {
      if (!foundOccupiedTile && GetBoardPositionType(i, j) != NONE) { foundOccupiedTile = true; }
      if (foundOccupiedTile && GetBoardPositionType(i, j) == NONE)  { m_ThisFrameCoveredTiles++; }
    }
  }

  reward -= (m_ThisFrameCoveredTiles - m_LastFrameCoveredTiles) * COVERED_TILE_PENALTY;
  reward -= (m_ThisFrameLinesOverHeightLimit - m_LastFrameLinesOverHeightLimit) * LINE_HEIGHT_LIMIT_PENALTY;
  if (m_ToppedOut) { reward -= TOP_OUT_PENALTY; }

  return reward;
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

  if (!TetrominoInValidPosition(m_CurrentTetromino)) { m_ToppedOut = true; }
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
