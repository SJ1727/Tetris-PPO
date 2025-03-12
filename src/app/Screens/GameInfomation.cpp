#include "app/Screens/GameInfomation.hpp"

void GameInfomationScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Defining components settings */
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };
  
  LabelSettings scoringInfomationLabelSettings;
  SetLabelStyle(&scoringInfomationLabelSettings, LEFT_CORNER_RADIUS(20));
  scoringInfomationLabelSettings.image = { resourceManager->GetImage("Scoring Infomation"), 400, 460 };
  
  LabelSettings goalLabelSettings;
  SetLabelStyle(&goalLabelSettings, RIGHT_CORNER_RADIUS(20));
  goalLabelSettings.image = { resourceManager->GetImage("Game Goals"), 284, 336 };
  
  /* Create components */
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings); 

  CREATE_LABEL(scoringInfomationLabel, 0, 10, 400, 460, scoringInfomationLabelSettings);
  CREATE_LABEL(goalLabel, 516, 10, 284, 336, goalLabelSettings);
  
  /* Adding bindings to components */
  returnButton->BindClick(CHANGE_SCREEN(screenManager, MAIN_MENU));
  
  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
