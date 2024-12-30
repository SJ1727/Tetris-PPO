#include "app/Screens/Settings.hpp"

void SettingsScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 32, "Def 32");
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
  m_ResourceManager.LoadImage("resources/images/return_icon.png", "Return Icon");
}

void SettingsScreen::Init(ScreenManager* screenManager) {
  LoadResources();

  const SDL_Color BACKGROUND_COLOR = { 22, 22, 22, 255 };
  const SDL_Color BUTTON_COLOR = { 76, 75, 75, 255 };
  const SDL_Color LABEL_COLOR = { 51, 51, 51, 255 };

  TTF_Font* titleFont = m_ResourceManager.GetFont("Def 70");
  TTF_Font* normalFont = m_ResourceManager.GetFont("Def 32");
  SDL_Surface* returnIcon = m_ResourceManager.GetImage("Return Icon");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);

  
  /* Defining components settings */
  LabelSettings titleTextSettings;
  titleTextSettings.text = "Settings";
  titleTextSettings.font = titleFont;
  titleTextSettings.textColor = WHITE;
  titleTextSettings.backgroundColor = TRANSPARENT;
  
  ButtonSettings returnButtonSettings;
  returnButtonSettings.imageDefault = { returnIcon, 40, 40 };
  returnButtonSettings.backgroundDefaultColor = BUTTON_COLOR;
  returnButtonSettings.cornerRadius = { 20, 20, 0, 0 };
  
  ButtonSettings volumeButtonSettings;
  volumeButtonSettings.text = "Volume";
  volumeButtonSettings.font = normalFont;
  volumeButtonSettings.textColor = WHITE;
  volumeButtonSettings.backgroundDefaultColor = BUTTON_COLOR;
  volumeButtonSettings.cornerRadius = { 20, 0, 20, 0 };
  
  ButtonSettings controlButtonSettings;
  controlButtonSettings.text = "Controls";
  controlButtonSettings.font = normalFont;
  controlButtonSettings.textColor = WHITE;
  controlButtonSettings.backgroundDefaultColor = BUTTON_COLOR;
  controlButtonSettings.cornerRadius = { 20, 0, 20, 0 };
  
  ButtonSettings aiButtonSettings;
  aiButtonSettings.text = "AI Player";
  aiButtonSettings.font = normalFont;
  aiButtonSettings.textColor = WHITE;
  aiButtonSettings.backgroundDefaultColor = BUTTON_COLOR;
  aiButtonSettings.cornerRadius = { 20, 0, 20, 0 };
  
  ButtonSettings resetDataButtonSettings;
  resetDataButtonSettings.text = "Reset Data";
  resetDataButtonSettings.font = normalFont;
  resetDataButtonSettings.textColor = WHITE;
  resetDataButtonSettings.backgroundDefaultColor = BUTTON_COLOR;
  resetDataButtonSettings.cornerRadius = { 0, 20, 0, 20 };
  
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
