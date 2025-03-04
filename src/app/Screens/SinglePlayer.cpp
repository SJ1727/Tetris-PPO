#include "app/Screens/SinglePlayer.hpp"

void SinglePlayerGameScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  auto board = new TetrisBoardDisplay(20, 20, 100, 200, new TetrisEngine(), m_Context->player1KeyBindings);
  Link(board, "Board");

  auto board2 = new TetrisBoardDisplay(220, 20, 100, 200, new TetrisEngine(), m_Context->player2KeyBindings);
  Link(board2, "Board2");
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Game Music"), -1);
}
