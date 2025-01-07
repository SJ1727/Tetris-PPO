#include "app/Screens/MainMenu.hpp"

void MainMenuScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Tetris";
  titleTextSettings.font = resourceManager->GetFont("Font 70");

  ButtonSettings singlePlayerButtonSettings;
  SetButtonStyle(&singlePlayerButtonSettings, RIGHT_CORNER_RADIUS(20));
  singlePlayerButtonSettings.text = "Single Player";
  singlePlayerButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings localMultiButtonSettings;
  SetButtonStyle(&localMultiButtonSettings, RIGHT_CORNER_RADIUS(20));
  localMultiButtonSettings.text = "Local Multiplayer";
  localMultiButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings versusAiButtonSettings;
  SetButtonStyle(&versusAiButtonSettings, RIGHT_CORNER_RADIUS(20));
  versusAiButtonSettings.text = "Player vs AI";
  versusAiButtonSettings.font = resourceManager->GetFont("Font 32");

  ButtonSettings settingsButtonSettings;
  SetButtonStyle(&settingsButtonSettings, BOTTOM_CORNER_RADIUS(20));
  settingsButtonSettings.imageDefault = { resourceManager->GetImage("Settings Icon"), 40, 40 };
  settingsButtonSettings.onClickSound = resourceManager->GetSoundEffect("Button Click");

  ButtonSettings helpButtonSettings;
  SetButtonStyle(&helpButtonSettings, BOTTOM_CORNER_RADIUS(20));
  helpButtonSettings.imageDefault = { resourceManager->GetImage("Question Mark Icon"), 40, 40 };
  helpButtonSettings.onClickSound = resourceManager->GetSoundEffect("Button Click");

  LabelSettings gameInfomationBackgroundSettings;
  SetLabelStyle(&gameInfomationBackgroundSettings, LEFT_CORNER_RADIUS(20));
  
  LabelSettings highScoreLabelSettings;
  highScoreLabelSettings.text = "High Score";
  highScoreLabelSettings.font = resourceManager->GetFont("Font 32");
  highScoreLabelSettings.textColor = WHITE;
  
  LabelSettings highScoreNumberLabelSettings;
  highScoreNumberLabelSettings.text = "xxx";
  highScoreNumberLabelSettings.font = resourceManager->GetFont("Font 32");
  highScoreNumberLabelSettings.textColor = WHITE;
  
  LabelSettings mostLinesLabelSettings;
  mostLinesLabelSettings.text = "Most Lines Cleared";
  mostLinesLabelSettings.font = resourceManager->GetFont("Font 32");
  mostLinesLabelSettings.textColor = WHITE;
  
  LabelSettings mostLinesNumberLabelSettings;
  mostLinesNumberLabelSettings.text = "xxx";
  mostLinesNumberLabelSettings.font = resourceManager->GetFont("Font 32");
  mostLinesNumberLabelSettings.textColor = WHITE;
  
  LabelSettings timePlayedLabelSettings;
  timePlayedLabelSettings.text = "Hours Played";
  timePlayedLabelSettings.font = resourceManager->GetFont("Font 32");
  timePlayedLabelSettings.textColor = WHITE;
  
  LabelSettings timePlayedNumberLabelSettings;
  timePlayedNumberLabelSettings.text = "xxx";
  timePlayedNumberLabelSettings.font = resourceManager->GetFont("Font 32");
  timePlayedNumberLabelSettings.textColor = WHITE;

  /* Create components */
  CREATE_LABEL(titleText, 528, 10, 100, 100, titleTextSettings);

  CREATE_BUTTON(singlePlayerButton, 440, 140, 360, 80, singlePlayerButtonSettings); 
  CREATE_BUTTON(localMultiButton, 440, 260, 360, 80, localMultiButtonSettings); 
  CREATE_BUTTON(versusAiButton, 440, 380, 360, 80, versusAiButtonSettings); 
  
  CREATE_BUTTON(settingsButton, 480, 520, 80, 80, settingsButtonSettings); 
  CREATE_BUTTON(helpButton, 640, 520, 80, 80, helpButtonSettings); 

  CREATE_LABEL(gameInfomationBackground, 0, 50, 280, 500, gameInfomationBackgroundSettings);
  CREATE_LINE(gameInfomationLine1, 0, 206, 280, 206, BACKGROUND_COLOR);
  CREATE_LINE(gameInfomationLine2, 0, 374, 280, 374, BACKGROUND_COLOR);
  CREATE_LABEL(highScoreLabel, 68, 60, 122, 34, highScoreLabelSettings);
  CREATE_LABEL(highScoreNumberLabel, 108, 124, 42, 34, highScoreNumberLabelSettings);
  CREATE_LABEL(mostLinesLabel, 34, 216, 204, 34, mostLinesLabelSettings);
  CREATE_LABEL(mostLinesNumberLabel, 108, 284, 42, 34, mostLinesNumberLabelSettings);
  CREATE_LABEL(timePlayedLabel, 58, 384, 146, 34, timePlayedLabelSettings);
  CREATE_LABEL(timePlayedNumberLabel, 108, 446, 42, 34, timePlayedNumberLabelSettings);

  /* Create Animations */
  CREATE_ANIMATION(singlePlayerButtonAnimation, AnimateButtonStretchLeft, singlePlayerButton, 30, 300);
  CREATE_ANIMATION(localMultiButtonAnimation, AnimateButtonStretchLeft, localMultiButton, 30, 300);
  CREATE_ANIMATION(versusAiButtonAnimation, AnimateButtonStretchLeft, versusAiButton, 30, 300);
  CREATE_ANIMATION(settingButtonAnimation, AnimateButtonStretchUp, settingsButton, 10, 300);
  CREATE_ANIMATION(helpButtonAnimation, AnimateButtonStretchUp, helpButton, 10, 300);

  /* Adding bindings to components */
  singlePlayerButton->AddHoverAnimation(singlePlayerButtonAnimation);
  localMultiButton->AddHoverAnimation(localMultiButtonAnimation);
  versusAiButton->AddHoverAnimation(versusAiButtonAnimation);
  settingsButton->AddHoverAnimation(settingButtonAnimation);
  helpButton->AddHoverAnimation(helpButtonAnimation);

  singlePlayerButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SINGLE_PLAYER_GAME));
  settingsButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
