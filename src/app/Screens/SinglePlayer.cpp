#include "app/Screens/SinglePlayer.hpp"

void SinglePlayerGameScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);
  
  /* Defining components settings */
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };

  LabelSettings heldTetrominoLabelSettings;
  SetLabelStyle(&heldTetrominoLabelSettings, LEFT_CORNER_RADIUS(20));
  heldTetrominoLabelSettings.imageDefault = nullptr;

  /* Create components */
  auto board = new TetrisBoardDisplay(270, 40, 260, 520, m_Context->singlePlayerEngine, m_Context->player1KeyBindings);
  Link(board, "Board");
  
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings); 
  CREATE_LABEL(heldTetrominoLabel, 0, 40, 230, 160, heldTetrominoLabelSettings);

  m_HeldTetrominoLabel = heldTetrominoLabel;
  
  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  
  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, MAIN_MENU));

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Game Music"), -1);
}
  
void SinglePlayerGameScreen::UpdateHeldTetrominoLabel() {
  TetrominoType heldTetrominoType = m_Context->singlePlayerEngine->GetHeldTetrominoType();

  switch (heldTetrominoType) {
    case O:
      m_HeldTetrominoLabel->
  }
}
