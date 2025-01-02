#include "app/Screens/ControlSettings.hpp"

void ControlSettingsScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
  m_ResourceManager.LoadFont("resources/font/ahronbd.ttf", 20, "Default font 25");
  m_ResourceManager.LoadImage("resources/images/return_icon.png", "Return Icon");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}

void ControlSettingsScreen::Init(ScreenManager* screenManager) {
  LoadResources();

  TTF_Font* titleFont = m_ResourceManager.GetFont("Def 70");
  TTF_Font* normalFont = m_ResourceManager.GetFont("Default font 25");
  SDL_Surface* returnIcon = m_ResourceManager.GetImage("Return Icon");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);
  
  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
