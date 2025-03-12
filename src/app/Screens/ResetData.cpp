#include "app/Screens/ResetData.hpp"

void ResetDataScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings warningLabelSettings1;
  warningLabelSettings1.text = "Are you sure you want";
  warningLabelSettings1.textColor = WHITE;
  warningLabelSettings1.font = resourceManager->GetFont("Font 70");
  
  LabelSettings warningLabelSettings2;
  warningLabelSettings2.text = "to reset your data?";
  warningLabelSettings2.textColor = WHITE;
  warningLabelSettings2.font = resourceManager->GetFont("Font 70");

  LabelSettings warningLabelSettings3;
  warningLabelSettings3.text = "You cannot undo this action";
  warningLabelSettings3.textColor = WHITE;
  warningLabelSettings3.font = resourceManager->GetFont("Font 70");

  ButtonSettings yesButtonSettings;
  SetButtonStyle(&yesButtonSettings, LEFT_CORNER_RADIUS(20));
  yesButtonSettings.text = "Yes";
  yesButtonSettings.textColor = WHITE;
  yesButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings noButtonSettings;
  SetButtonStyle(&noButtonSettings, RIGHT_CORNER_RADIUS(20));
  noButtonSettings.text = "No";
  noButtonSettings.textColor = WHITE;
  noButtonSettings.font = resourceManager->GetFont("Font 32");
  
  /* Create components */
  CREATE_LABEL(warningLabel1, 0, 70, 800, 70, warningLabelSettings1);
  CREATE_LABEL(warningLabel2, 0, 140, 800, 70, warningLabelSettings2);
  CREATE_LABEL(warningLabel3, 0, 250, 800, 70, warningLabelSettings3);

  CREATE_BUTTON(yesButton, 0, 400, 360, 80, yesButtonSettings);
  CREATE_BUTTON(noButton, 440, 400, 360, 80, noButtonSettings);
  
  /* Adding bindings to components */
  yesButton->BindClick(std::bind([](int& highScore, int& mostLinesCleared, float& timePlayed, std::shared_ptr<ScreenManager> screenManager) {
    highScore = 0;
    mostLinesCleared = 0;
    timePlayed = 0.0;
    screenManager->SetScreen(SETTINGS);
  }, std::ref(m_Context->highScore), std::ref(m_Context->mostLinesCleared), std::ref(m_Context->timePlayedSeconds), screenManager));

  noButton->BindClick(CHANGE_SCREEN(screenManager, SETTINGS));
  
  /* Create Animations */
  CREATE_ANIMATION(yesButtonAnimation, AnimateButtonStretchRight, yesButton, 30, 300);
  CREATE_ANIMATION(noButtonAnimation, AnimateButtonStretchLeft, noButton, 30, 300);
  
  /* Adding bindings to components */
  yesButton ->AddHoverAnimation(yesButtonAnimation);
  noButton  ->AddHoverAnimation(noButtonAnimation);
  
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}

