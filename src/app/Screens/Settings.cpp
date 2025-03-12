#include "app/Screens/Settings.hpp"

void SettingsScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);
  
  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Settings";
  titleTextSettings.font = resourceManager->GetFont("Font 70");
  
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };
  
  ButtonSettings volumeButtonSettings;
  SetButtonStyle(&volumeButtonSettings, RIGHT_CORNER_RADIUS(20));
  volumeButtonSettings.text = "Volume";
  volumeButtonSettings.font = resourceManager->GetFont("Font 32");

  ButtonSettings controlButtonSettings;
  SetButtonStyle(&controlButtonSettings, RIGHT_CORNER_RADIUS(20));
  controlButtonSettings.text = "Controls";
  controlButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings aiButtonSettings;
  SetButtonStyle(&aiButtonSettings, RIGHT_CORNER_RADIUS(20));
  aiButtonSettings.text = "AI Player";
  aiButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings resetDataButtonSettings;
  SetButtonStyle(&resetDataButtonSettings, LEFT_CORNER_RADIUS(20));
  resetDataButtonSettings.text = "Reset Data";
  resetDataButtonSettings.font = resourceManager->GetFont("Font 32");
  
  /* Create components */
  CREATE_LABEL(titleText, 528, 10, 100, 100, titleTextSettings);
  
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings); 
  
  CREATE_BUTTON(volumeButton, 440, 140, 360, 80, volumeButtonSettings); 
  CREATE_BUTTON(controlButton, 440, 260, 360, 80, controlButtonSettings); 
  CREATE_BUTTON(aiButton, 440, 380, 360, 80, aiButtonSettings); 
  CREATE_BUTTON(resetDataButton, 0, 140, 360, 80, resetDataButtonSettings); 
  
  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  CREATE_ANIMATION(volumeButtonAnimation, AnimateButtonStretchLeft, volumeButton, 30, 300);
  CREATE_ANIMATION(controlButtonAnimation, AnimateButtonStretchLeft, controlButton, 30, 300);
  CREATE_ANIMATION(aiButtonAnimation, AnimateButtonStretchLeft, aiButton, 30, 300);
  CREATE_ANIMATION(resetDataButtonAnimation, AnimateButtonStretchRight, resetDataButton, 30, 300);

  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  volumeButton->AddHoverAnimation(volumeButtonAnimation);
  controlButton->AddHoverAnimation(controlButtonAnimation);
  aiButton->AddHoverAnimation(aiButtonAnimation);
  resetDataButton->AddHoverAnimation(resetDataButtonAnimation);

  returnButton->BindClick(CHANGE_SCREEN(screenManager, MAIN_MENU));
  volumeButton->BindClick(CHANGE_SCREEN(screenManager, VOLUME_SETTINGS));
  controlButton->BindClick(CHANGE_SCREEN(screenManager, CONTROL_SETTINGS));
  aiButton->BindClick(CHANGE_SCREEN(screenManager, AI_SETTINGS));
  
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
