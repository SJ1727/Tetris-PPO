#include "app/WindowComponents/TetrisBoardDisplay.hpp"

TetrisBoardDisplay::TetrisBoardDisplay(int x, int y, int width, int height, TetrisEngine* tetrisEngine, KeyBindings controls) :
  m_X(x), m_Y(y), m_Width(width), m_Height(height), m_TetrisEngine(tetrisEngine), m_Controls(controls) {

}

void TetrisBoardDisplay::Render(SDL_Renderer* renderer) {
  // Draws the blackbackground
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_FRect background = CreateFRect(m_X, m_Y, m_Width, m_Height);
  SDL_RenderFillRect(renderer, &background);

  DrawGrid(renderer);

  DrawCells(renderer);
}

void TetrisBoardDisplay::DrawGrid(SDL_Renderer* renderer) {
  int cellWidth = m_Width / s_Columns;
  int cellHeight = m_Height / s_Rows;

  SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);
    
  // Draw vertical lines
  for (int i = 0; i <= s_Columns; i++) {
    int x = i * cellWidth;
    SDL_RenderLine(renderer, i * cellWidth + m_X, m_Y, i * cellWidth + m_X, m_Height + m_Y);
  }
    
  // Draw horizontal lines
  for (int i = 0; i <= s_Rows; i++) {
    int y = i * cellHeight;
    SDL_RenderLine(renderer, m_X, i * cellHeight + m_Y, m_Width + m_X, i * cellHeight + m_Y);
  }
}

void TetrisBoardDisplay::DrawCells(SDL_Renderer* renderer) {
  SDL_FRect cellRect;
  SDL_Color cellColor;
  auto board = m_TetrisEngine->GetBoard(); 
  int cellWidth = m_Width / s_Columns;
  int cellHeight = m_Height / s_Rows;

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  for (int i = 0; i < s_Columns; i++) {
    for (int j = 0; j < s_Rows; j++) {
      cellColor = TetrominoTypeToColor(board[j * s_Columns + i]);
      cellRect = CreateFRect(m_X + cellWidth * i, m_Y + cellHeight * j, cellWidth, cellHeight);
      
      SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
      SDL_RenderFillRect(renderer, &cellRect);
    }
  }
}

SDL_Color TetrisBoardDisplay::TetrominoTypeToColor(TetrominoType type) {
  switch (type) {
    case I:
      return { 0, 255, 255, 255};
    case J:
      return { 0, 0, 255, 255 };
    case L:
      return { 255, 85, 0, 255 };
    case S:
      return { 0, 255, 0, 255 };
    case T:
      return { 255, 0, 255, 255 };
    case Z:
      return { 255, 0, 0, 255 };
    case O:
      return { 255, 255, 0, 255 };
    default:
      return { 0, 0, 0, 0 };
  }
}

void TetrisBoardDisplay::HandleEvents(SDL_Event* event) {
  if (event->type != SDL_EVENT_KEY_DOWN) { return; }

  // Maps the keyboard input to the corresponding move in the tetris game depending on  the keybindings
  if (event->key.key == m_Controls.right)             { m_TetrisEngine->SetNextMove(RIGHT); }
  else if (event->key.key == m_Controls.left)         { m_TetrisEngine->SetNextMove(LEFT); }
  else if (event->key.key == m_Controls.down)         { m_TetrisEngine->SetNextMove(DOWN); }
  else if (event->key.key == m_Controls.rotateRight)  { m_TetrisEngine->SetNextMove(ROTATE_RIGHT); }
  else if (event->key.key == m_Controls.rotateLeft)   { m_TetrisEngine->SetNextMove(ROTATE_LEFT); }
  else if (event->key.key == m_Controls.drop)         { m_TetrisEngine->SetNextMove(DROP); }
  else if (event->key.key == m_Controls.hold)         { m_TetrisEngine->SetNextMove(HOLD); }
}

void TetrisBoardDisplay::Update() {
  m_TetrisEngine->Update();
}
