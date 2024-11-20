#include "app/Screens/SinglePlayer.hpp"

void SinglePlayerGameScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/ahronbd.ttf", 20, "Default font 12");
  m_ResourceManager.LoadMusic("resources/sound/Korobeiniki_piano.ogg", "Game Music");
}

void SinglePlayerGameScreen::Init(ScreenManager* screenManager) {
  LoadResources();

  TTF_Font* font = m_ResourceManager.GetFont("Default font 12");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BLACK);

  /* Defining components settings */
  LabelSettings testLabelSettings;
  testLabelSettings.text = "Game";
  testLabelSettings.font = font;
  testLabelSettings.textColor = BLACK;
  testLabelSettings.backgroundColor = WHITE;

  ButtonSettings quitSettings;
  quitSettings.text = "Quit";
  quitSettings.font = font;
  quitSettings.textColor = WHITE;
  quitSettings.backgroundDefaultColor = RED;
  quitSettings.backgroundClickedColor = GREEN;

  /* Create components */
  Label* testLabel = new Label(20, 150, 300, 300, testLabelSettings);
  Button* quitButton = new Button(20, 20, 100, 50, quitSettings);
  
  quitButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, MAIN_MENU));
  
  /* Linking the components to the screen */
  Link(testLabel);
  Link(quitButton);
  
  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Game Music");
  Mix_PlayMusic(music, -1);
}
