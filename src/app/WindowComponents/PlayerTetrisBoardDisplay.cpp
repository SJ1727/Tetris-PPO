#include "app/WindowComponents/PlayerTetrisBoardDisplay.hpp"

PlayerTetrisBoardDisplay::PlayerTetrisBoardDisplay(int x, int y, int width, int height, TetrisEngine* tetrisEngine, KeyBindings controls) 
  : TetrisBoardDisplay(x, y, width, height, tetrisEngine), m_Controls(controls) {
  
}

void PlayerTetrisBoardDisplay::HandleEvents(SDL_Event* event) {
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
