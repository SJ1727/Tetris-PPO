#include "app/WindowComponents/TetrisBoardDisplay.hpp"

TetrisBoardDisplay::TetrisBoardDisplay(int x, int y, int width, int height, TetrisEngine* tetrisEngine, KeyBindings controls) :
  m_X(x), m_Y(y), m_Width(width), m_Height(height), m_TetrisEngine(tetrisEngine), m_Controls(controls) {

}

TetrisBoardDisplay::Render(SDL_Renderer* renderer) {
  // Draws the blackbackground
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_Rect background = { m_X, m_Y, m_Width, m_Height };
  SDL_RenderFillRect(renderer, &background);

  SDL_SetRenderDrawColor(renderer, )
}

TetrisBoardDisplay::DrawGrid(SDL_Renderer* renderer) {
  
}

TetrisBoardDisplay::HandleEvents(SDL_Event* event) {
  if (event->type != SDL_EVENT_KEY_DOWN) { return; }

  // Maps the keyboard input to the corresponding move in the tetris game depending on  the keybindings
  switch (event->key.keysym.sym) {
    case m_Controls.right:
      m_TetrisEngine.SetNextMove(RIGHT);
      break;
    case m_Controls.left:
      m_TetrisEngine.SetNextMove(LEFT);
      break;
    case m_Controls.down:
      m_TetrisEngine.SetNextMove(DOWN);
      break;
    case m_Controls.rotateRight:
      m_TetrisEngine.SetNextMove(ROTATE_RIGHT);
      break;
    case m_Controls.rotateLeft:
      m_TetrisEngine.SetNextMove(ROTATE_LEFT);
      break;
    case m_Controls.drop:
      m_TetrisEngine.SetNextMove(DROP);
      break;
    case m_Controls.hold:
      m_TetrisEngine.SetNextMove(HOLD);
      break;
  }
}
