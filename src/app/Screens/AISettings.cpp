#include "app/Screens/AISettings.hpp"

void AISettingsScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/ahronbd.ttf", 25, "Default font 25");
  m_ResourceManager.LoadFont("resources/font/JetBrainsMonoNerdFont-Medium.ttf", 15, "Text field");
  m_ResourceManager.LoadImage("resources/images/return_icon.png", "Return Icon");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}

void AISettingsScreen::Init(ScreenManager* screenManager) {
  LoadResources();
  
  TTF_Font* normalFont = m_ResourceManager.GetFont("Default font 25");
  TTF_Font* textFieldFont = m_ResourceManager.GetFont("Text field");
  SDL_Surface* returnIcon = m_ResourceManager.GetImage("Return Icon");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);
  
  /* Defining components settings */
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { returnIcon, 40, 40 };
  
  LabelSettings modelPathLabelSettings;
  modelPathLabelSettings.text = "MODEL PATH";
  modelPathLabelSettings.font = normalFont;
  modelPathLabelSettings.textColor = WHITE;
  modelPathLabelSettings.textCenteredX = false;
  
  TextFieldSettings modelPathFieldSettings;
  modelPathFieldSettings.initialText = "example/path/model.onnx";
  modelPathFieldSettings.font = textFieldFont;
  
  /* Create components */
  Button* returnButton = new Button(20, 530, 50, 50, returnButtonSettings);
  Label* modelPathLabel = new Label(20, 20, 200, 50, modelPathLabelSettings);
  TextField* modelPathField = new TextField(190, 30, 400, 25, modelPathFieldSettings);
  
  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));
  
  /* Linking the components to the screen */
  Link(returnButton);
  Link(modelPathLabel);
  Link(modelPathField);
  
  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
