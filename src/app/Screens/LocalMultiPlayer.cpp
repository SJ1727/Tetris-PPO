#include "app/Screens/LocalMultiPlayer.hpp"

void LocalMultiPlayerGameScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);
  
  m_ITetromino = { resourceManager->GetImage("I Tetromino"), 102, 24 };
  m_JTetromino = { resourceManager->GetImage("J Tetromino"), 76, 50 };
  m_LTetromino = { resourceManager->GetImage("L Tetromino"), 76, 50 };
  m_OTetromino = { resourceManager->GetImage("O Tetromino"), 50, 50 };
  m_STetromino = { resourceManager->GetImage("S Tetromino"), 76, 50 };
  m_TTetromino = { resourceManager->GetImage("T Tetromino"), 76, 50 };
  m_ZTetromino = { resourceManager->GetImage("Z Tetromino"), 76, 50 };
  
  /* Defining components settings */
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };
  
  LabelSettings gameInfomationBackgroundSettings;
  SetLabelStyle(&gameInfomationBackgroundSettings, TOP_CORNER_RADIUS(20));


  /* Held Tetromino */
  LabelSettings heldTetrominoLabelSettings;
  
  LabelSettings heldTetrominoTextLabelSettings;
  heldTetrominoTextLabelSettings.text = "Hold";
  heldTetrominoTextLabelSettings.textColor = WHITE;
  heldTetrominoTextLabelSettings.font = resourceManager->GetFont("Font 32");


  /* Next Tetromino */
  LabelSettings nextTetrominoLabelSettings;

  LabelSettings nextTetrominoTextLabelSettings;
  nextTetrominoTextLabelSettings.text = "Next";
  nextTetrominoTextLabelSettings.textColor = WHITE;
  nextTetrominoTextLabelSettings.font = resourceManager->GetFont("Font 32");
 

  /* Score */
  LabelSettings scoreLabelSettings;
  scoreLabelSettings.text = "Score";
  scoreLabelSettings.textColor = WHITE;
  scoreLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings scoreNumberLabelSettings;
  scoreNumberLabelSettings.text = "0";
  scoreNumberLabelSettings.textColor = WHITE;
  scoreNumberLabelSettings.font = resourceManager->GetFont("Font 32");
 

  /* Lines Cleared */
  LabelSettings linesClearedLabelSettings;
  linesClearedLabelSettings.text = "Lines Cleared";
  linesClearedLabelSettings.textColor = WHITE;
  linesClearedLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings linesClearedNumberLabelSettings;
  linesClearedNumberLabelSettings.text = "0";
  linesClearedNumberLabelSettings.textColor = WHITE;
  linesClearedNumberLabelSettings.font = resourceManager->GetFont("Font 32");
 

  /* Level */
  LabelSettings levelLabelSettings;
  levelLabelSettings.text = "Level";
  levelLabelSettings.textColor = WHITE;
  levelLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings levelNumberLabelSettings;
  levelNumberLabelSettings.text = "0";
  levelNumberLabelSettings.textColor = WHITE;
  levelNumberLabelSettings.font = resourceManager->GetFont("Font 32");

  /* Board Titles */
  LabelSettings player1LabelSettings;
  player1LabelSettings.text = "Player 1";
  player1LabelSettings.textColor = WHITE;
  player1LabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings player2LabelSettings;
  player2LabelSettings.text = "Player 2";
  player2LabelSettings.textColor = WHITE;
  player2LabelSettings.font = resourceManager->GetFont("Font 32");


  /* Create components */
  auto board1 = new PlayerTetrisBoardDisplay(530, 50, 260, 520, m_Context->localPlayer1Engine, m_Context->player1KeyBindings);
  Link(board1, "Board1");
  
  auto board2 = new PlayerTetrisBoardDisplay(10, 50, 260, 520, m_Context->localPlayer2Engine, m_Context->player2KeyBindings);
  Link(board2, "Board2");
  
  CREATE_BUTTON(returnButton, 360, 520, 80, 80, returnButtonSettings);

  CREATE_LABEL(player1Label, 520, 0, 280, 50, player1LabelSettings);
  CREATE_LABEL(player2Label, 0, 0, 280, 50, player2LabelSettings);
  
  CREATE_LABEL(heldTetrominoLabel1, 410, 190, 100, 80, heldTetrominoLabelSettings);
  CREATE_LABEL(heldTetrominoLabel2, 290, 190, 100, 80, heldTetrominoLabelSettings);
  CREATE_LABEL(heldTetrominoTextLabel, 320, 140, 160, 50, heldTetrominoTextLabelSettings);

  CREATE_LABEL(nextTetrominoLabel1, 410, 50, 100, 80, nextTetrominoLabelSettings);
  CREATE_LABEL(nextTetrominoLabel2, 290, 50, 100, 80, nextTetrominoLabelSettings);
  CREATE_LABEL(nextTetrominoTextLabel, 320, 0, 160, 50, nextTetrominoTextLabelSettings);

  CREATE_LABEL(gameInfomationBackground, 280, 0, 240, 490, gameInfomationBackgroundSettings);
  CREATE_LINE(gameInfomationLine1, 280, 140, 520, 140, BACKGROUND_COLOR);
  CREATE_LINE(gameInfomationLine2, 280, 280, 520, 280, BACKGROUND_COLOR);
  CREATE_LINE(gameInfomationLine3, 280, 350, 520, 350, BACKGROUND_COLOR);
  CREATE_LINE(gameInfomationLine4, 280, 420, 520, 420, BACKGROUND_COLOR);

  CREATE_LABEL(scoreLabel, 320, 280, 160, 50, scoreLabelSettings);
  CREATE_LABEL(scoreNumberLabel1, 410, 310, 100, 50, scoreNumberLabelSettings);
  CREATE_LABEL(scoreNumberLabel2, 290, 310, 100, 50, scoreNumberLabelSettings);

  CREATE_LABEL(linesClearedLabel, 320, 350, 160, 50, linesClearedLabelSettings);
  CREATE_LABEL(linesClearedNumberLabel1, 410, 380, 100, 50, linesClearedNumberLabelSettings);
  CREATE_LABEL(linesClearedNumberLabel2, 290, 380, 100, 50, linesClearedNumberLabelSettings);

  CREATE_LABEL(levelLabel, 320, 420, 160, 50, levelLabelSettings);
  CREATE_LABEL(levelNumberLabel1, 410, 450, 100, 50, levelNumberLabelSettings);
  CREATE_LABEL(levelNumberLabel2, 290, 450, 100, 50, levelNumberLabelSettings);

  m_HeldTetrominoLabel1 = heldTetrominoLabel1;
  m_NextTetrominoLabel1 = nextTetrominoLabel1;
  m_scoreLabel1         = scoreNumberLabel1;
  m_linesClearedLabel1  = linesClearedNumberLabel1;
  m_levelLabel1         = levelNumberLabel1;
  
  m_HeldTetrominoLabel2 = heldTetrominoLabel2;
  m_NextTetrominoLabel2 = nextTetrominoLabel2;
  m_scoreLabel2         = scoreNumberLabel2;
  m_linesClearedLabel2  = linesClearedNumberLabel2;
  m_levelLabel2         = levelNumberLabel2;
  
  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  
  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, MAIN_MENU));

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Game Music"), -1);
}

void LocalMultiPlayerGameScreen::Update() {
  // Updating held tetromino display
  m_HeldTetrominoLabel1->UpdateImage(
    TetrominoTypeToImage(m_Context->localPlayer1Engine->GetHeldTetrominoType())
  );
  m_HeldTetrominoLabel2->UpdateImage(
    TetrominoTypeToImage(m_Context->localPlayer2Engine->GetHeldTetrominoType())
  );
  
  // Updating next tetromino display
  m_NextTetrominoLabel1->UpdateImage(
    TetrominoTypeToImage(m_Context->localPlayer1Engine->PeakNextTetrominoType())
  );
  m_NextTetrominoLabel2->UpdateImage(
    TetrominoTypeToImage(m_Context->localPlayer2Engine->PeakNextTetrominoType())
  );


  // Updating the game infomation display
  m_scoreLabel1->UpdateText(
    std::to_string(m_Context->localPlayer1Engine->GetScore())
  );
  m_linesClearedLabel1->UpdateText(
    std::to_string(m_Context->localPlayer1Engine->GetLinesCleared())
  );
  m_levelLabel1->UpdateText(
    std::to_string(m_Context->localPlayer1Engine->GetLevel())
  );
  m_scoreLabel2->UpdateText(
    std::to_string(m_Context->localPlayer2Engine->GetScore())
  );
  m_linesClearedLabel2->UpdateText(
    std::to_string(m_Context->localPlayer2Engine->GetLinesCleared())
  );
  m_levelLabel2->UpdateText(
    std::to_string(m_Context->localPlayer2Engine->GetLevel())
  );

  Screen::Update();
}


Image LocalMultiPlayerGameScreen::TetrominoTypeToImage(TetrominoType type) {
  switch (type) {
    case I:
      return m_ITetromino;
    case J:
      return m_JTetromino;
    case L:
      return m_LTetromino;
    case O:
      return m_OTetromino;
    case S:
      return m_STetromino;
    case T:
      return m_TTetromino;
    case Z:
      return m_ZTetromino;
    default:
      return { nullptr, 0, 0};
  }
}
