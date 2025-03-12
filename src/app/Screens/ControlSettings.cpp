#include "app/Screens/ControlSettings.hpp"

void ControlSettingsScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);
  
  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Controls";
  titleTextSettings.font = resourceManager->GetFont("Font 70");
 
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };

  ButtonSettings player1ButtonSettings;
  SetButtonStyle(&player1ButtonSettings, LEFT_CORNER_RADIUS(20));
  player1ButtonSettings.text = "Player 1 Controls";
  player1ButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings player2ButtonSettings;
  SetButtonStyle(&player2ButtonSettings, LEFT_CORNER_RADIUS(20));
  player2ButtonSettings.text = "Player 2 Controls";
  player2ButtonSettings.font = resourceManager->GetFont("Font 32");
  
  /* Create components */
  CREATE_LABEL(titleText, 528, 10, 100, 100, titleTextSettings);
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings);
  CREATE_BUTTON(player1Button, 0, 140, 360, 80, player1ButtonSettings);
  CREATE_BUTTON(player2Button, 0, 380, 360, 80, player2ButtonSettings);


  returnButton->BindClick(CHANGE_SCREEN(screenManager, SETTINGS));
  player1Button->BindClick(CHANGE_SCREEN(screenManager, PLAYER_1_CONTROL_SETTINGS));
  player2Button->BindClick(CHANGE_SCREEN(screenManager, PLAYER_2_CONTROL_SETTINGS));


  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  CREATE_ANIMATION(player1ButtonAnimation, AnimateButtonStretchRight, player1Button, 30, 300);
  CREATE_ANIMATION(player2ButtonAnimation, AnimateButtonStretchRight, player2Button, 30, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  player1Button->AddHoverAnimation(player1ButtonAnimation);
  player2Button->AddHoverAnimation(player2ButtonAnimation);

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
