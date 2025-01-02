#include "app/Screens/Settings.hpp"

void SettingsScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 32, "Def 32");
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
  m_ResourceManager.LoadImage("resources/images/return_icon.png", "Return Icon");
}

void SettingsScreen::Init(ScreenManager* screenManager) {
  LoadResources();

  TTF_Font* titleFont = m_ResourceManager.GetFont("Def 70");
  TTF_Font* normalFont = m_ResourceManager.GetFont("Def 32");
  SDL_Surface* returnIcon = m_ResourceManager.GetImage("Return Icon");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);

  
  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Settings";
  titleTextSettings.font = titleFont;
  
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { returnIcon, 40, 40 };
  
  ButtonSettings volumeButtonSettings;
  SetButtonStyle(&volumeButtonSettings, RIGHT_CORNER_RADIUS(20));
  volumeButtonSettings.text = "Volume";
  volumeButtonSettings.font = normalFont;
  
  ButtonSettings controlButtonSettings;
  SetButtonStyle(&controlButtonSettings, RIGHT_CORNER_RADIUS(20));
  controlButtonSettings.text = "Controls";
  controlButtonSettings.font = normalFont;
  
  ButtonSettings aiButtonSettings;
  SetButtonStyle(&aiButtonSettings, RIGHT_CORNER_RADIUS(20));
  aiButtonSettings.text = "AI Player";
  aiButtonSettings.font = normalFont;
  
  ButtonSettings resetDataButtonSettings;
  SetButtonStyle(&resetDataButtonSettings, LEFT_CORNER_RADIUS(20));
  resetDataButtonSettings.text = "Reset Data";
  resetDataButtonSettings.font = normalFont;
  
  /* Create components */
  Label* titleText = new Label(528, 10, 100, 100, titleTextSettings);
  
  Button* returnButton = new Button(640, 520, 80, 80, returnButtonSettings); 
  
  Button* volumeButton = new Button(440, 140, 360, 80, volumeButtonSettings); 
  Button* controlButton = new Button(440, 260, 360, 80, controlButtonSettings); 
  Button* aiButton = new Button(440, 380, 360, 80, aiButtonSettings); 
  Button* resetDataButton = new Button(0, 140, 360, 80, resetDataButtonSettings); 
  
  /* Create Animations */
  Animation* returnButtonAnimation = AnimateButtonStretchUp(returnButton, 10, 300);
  Animation* volumeButtonAnimation = AnimateButtonStretchLeft(volumeButton, 30, 300);
  Animation* controlButtonAnimation = AnimateButtonStretchLeft(controlButton, 30, 300);
  Animation* aiButtonAnimation = AnimateButtonStretchLeft(aiButton, 30, 300);
  Animation* resetDataButtonAnimation = AnimateButtonStretchRight(resetDataButton, 30, 300);

  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  volumeButton->AddHoverAnimation(volumeButtonAnimation);
  controlButton->AddHoverAnimation(controlButtonAnimation);
  aiButton->AddHoverAnimation(aiButtonAnimation);
  resetDataButton->AddHoverAnimation(resetDataButtonAnimation);

  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, MAIN_MENU));
  volumeButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, VOLUME_SETTINGS));
  controlButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, CONTROL_SETTINGS));
  aiButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, AI_SETTINGS));
  
  /* Linking the components to the screen */
  Link(titleText);
  Link(returnButton);
  Link(volumeButton);
  Link(controlButton);
  Link(aiButton);
  Link(resetDataButton);
  
  /* Adding animations */
  AddAnimation(returnButtonAnimation);
  AddAnimation(volumeButtonAnimation);
  AddAnimation(controlButtonAnimation);
  AddAnimation(aiButtonAnimation);
  AddAnimation(resetDataButtonAnimation);

  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
