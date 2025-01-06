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
  Label* titleText = new Label(528, 10, 100, 100, titleTextSettings);
  
  Button* returnButton = new Button(640, 520, 80, 80, returnButtonSettings);

  Button* player1Button = new Button(0, 140, 360, 80, player1ButtonSettings);
  Button* player2Button = new Button(0, 380, 360, 80, player2ButtonSettings);


  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));
  player1Button->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, PLAYER_1_CONTROL_SETTINGS));
  player2Button->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, PLAYER_2_CONTROL_SETTINGS));


  /* Create Animations */
  Animation* returnButtonAnimation = AnimateButtonStretchUp(returnButton, 10, 300);
  Animation* player1ButtonAnimation = AnimateButtonStretchRight(player1Button, 30, 300);
  Animation* player2ButtonAnimation = AnimateButtonStretchRight(player2Button, 30, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  player1Button->AddHoverAnimation(player1ButtonAnimation);
  player2Button->AddHoverAnimation(player2ButtonAnimation);
  
  /* Linking the components to the screen */
  Link(titleText);
  Link(returnButton);
  Link(player1Button);
  Link(player2Button);

  /* Adding animations */
  AddAnimation(returnButtonAnimation);
  AddAnimation(player1ButtonAnimation);
  AddAnimation(player2ButtonAnimation);

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
