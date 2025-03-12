#include "app/Screens/SinglePlayer.hpp"

void SinglePlayerGameScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
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

  LabelSettings heldTetrominoLabelSettings;
  SetLabelStyle(&heldTetrominoLabelSettings, LEFT_CORNER_RADIUS(20));
  
  LabelSettings heldTetrominoTextLabelSettings;
  heldTetrominoTextLabelSettings.text = "Hold";
  heldTetrominoTextLabelSettings.textColor = WHITE;
  heldTetrominoTextLabelSettings.font = resourceManager->GetFont("Font 32");

  LabelSettings nextTetrominoLabelSettings;
  SetLabelStyle(&nextTetrominoLabelSettings, RIGHT_CORNER_RADIUS(20));

  LabelSettings nextTetrominoTextLabelSettings;
  nextTetrominoTextLabelSettings.text = "Next Tetromino";
  nextTetrominoTextLabelSettings.textColor = WHITE;
  nextTetrominoTextLabelSettings.font = resourceManager->GetFont("Font 32");

  LabelSettings gameInfomationBackgroundSettings;
  SetLabelStyle(&gameInfomationBackgroundSettings, LEFT_CORNER_RADIUS(20));

  LabelSettings scoreLabelSettings;
  scoreLabelSettings.text = "Score";
  scoreLabelSettings.textColor = WHITE;
  scoreLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings scoreNumberLabelSettings;
  scoreNumberLabelSettings.text = "0";
  scoreNumberLabelSettings.textColor = WHITE;
  scoreNumberLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings linesClearedLabelSettings;
  linesClearedLabelSettings.text = "Lines Cleared";
  linesClearedLabelSettings.textColor = WHITE;
  linesClearedLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings linesClearedNumberLabelSettings;
  linesClearedNumberLabelSettings.text = "0";
  linesClearedNumberLabelSettings.textColor = WHITE;
  linesClearedNumberLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings levelLabelSettings;
  levelLabelSettings.text = "Level";
  levelLabelSettings.textColor = WHITE;
  levelLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings levelNumberLabelSettings;
  levelNumberLabelSettings.text = "0";
  levelNumberLabelSettings.textColor = WHITE;
  levelNumberLabelSettings.font = resourceManager->GetFont("Font 32");


  /* Create components */
  auto board = new PlayerTetrisBoardDisplay(270, 40, 260, 520, m_Context->singlePlayerEngine, m_Context->player1KeyBindings);
  Link(board, "Board");
  
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings); 
  
  CREATE_LABEL(heldTetrominoLabel, 0, 40, 230, 160, heldTetrominoLabelSettings);
  CREATE_LABEL(heldTetrominoTextLabel, 0, 0, 230, 160, heldTetrominoTextLabelSettings);

  CREATE_LABEL(nextTetrominoLabel, 570, 40, 230, 160, nextTetrominoLabelSettings);
  CREATE_LABEL(nextTetrominoTextLabel, 570, 0, 230, 160, nextTetrominoTextLabelSettings);

  CREATE_LABEL(gameInfomationBackground, 0, 240, 230, 330, gameInfomationBackgroundSettings);
  CREATE_LINE(gameInfomationLine1, 0, 350, 240, 350, BACKGROUND_COLOR);
  CREATE_LINE(gameInfomationLine2, 0, 460, 240, 460, BACKGROUND_COLOR);

  CREATE_LABEL(scoreLabel, 0, 220, 230, 110, scoreLabelSettings);
  CREATE_LABEL(scoreNumberLabel, 0, 260, 230, 110, scoreNumberLabelSettings);

  CREATE_LABEL(linesClearedLabel, 0, 330, 230, 110, linesClearedLabelSettings);
  CREATE_LABEL(linesClearedNumberLabel, 0, 370, 230, 110, linesClearedNumberLabelSettings);

  CREATE_LABEL(levelLabel, 0, 440, 230, 110, levelLabelSettings);
  CREATE_LABEL(levelNumberLabel, 0, 480, 230, 100, levelNumberLabelSettings);

  m_HeldTetrominoLabel = heldTetrominoLabel;
  m_NextTetrominoLabel = nextTetrominoLabel;
  m_scoreLabel = scoreNumberLabel;
  m_linesClearedLabel = linesClearedNumberLabel;
  m_levelLabel = levelNumberLabel;
  
  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  
  returnButton->BindClick(CHANGE_SCREEN(screenManager, MAIN_MENU));

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Game Music"), -1);
}

void SinglePlayerGameScreen::Update() {
  UpdateNextTetrominoLabel();
  
  UpdateHeldTetrominoLabel();

  UpdateGameStatisticsLabel();

  m_Context->highScore        = std::max(m_Context->singlePlayerEngine->GetScore()       , m_Context->highScore);
  m_Context->mostLinesCleared = std::max(m_Context->singlePlayerEngine->GetLinesCleared(), m_Context->mostLinesCleared);

  Screen::Update();
}

void SinglePlayerGameScreen::UpdateNextTetrominoLabel() {
  TetrominoType nextTetrominoType = m_Context->singlePlayerEngine->PeakNextTetrominoType();

  m_NextTetrominoLabel->UpdateImage(TetrominoTypeToImage(nextTetrominoType));
}
  
void SinglePlayerGameScreen::UpdateHeldTetrominoLabel() {
  TetrominoType heldTetrominoType = m_Context->singlePlayerEngine->GetHeldTetrominoType();

  m_HeldTetrominoLabel->UpdateImage(TetrominoTypeToImage(heldTetrominoType));
}

void SinglePlayerGameScreen::UpdateGameStatisticsLabel() {
  int score         = m_Context->singlePlayerEngine->GetScore();
  int linesCleared  = m_Context->singlePlayerEngine->GetLinesCleared();
  int level         = m_Context->singlePlayerEngine->GetLevel();

  m_scoreLabel        ->UpdateText(std::to_string(score));
  m_linesClearedLabel ->UpdateText(std::to_string(linesCleared));
  m_levelLabel        ->UpdateText(std::to_string(level));
}

Image SinglePlayerGameScreen::TetrominoTypeToImage(TetrominoType type) {
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
