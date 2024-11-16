#include "app/Screens/SinglePlayer.hpp"
#include "app/Screens/ScreenFactory.hpp"

void SinglePlayerGameScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/ahronbd.ttf", 20, "Default font 12");
  m_resource_manager.loadMusic("resources/sound/Korobeiniki_piano.ogg", "Game Music");
}

void SinglePlayerGameScreen::init(ScreenManager* screen_manager) {
  loadResources();

  TTF_Font* font = m_resource_manager.getFont("Default font 12");
  m_background_surface = createSingleColorSurface(m_width, m_height, BLACK);

  /* Defining components settings */
  LabelSettings test_label_settings;
  test_label_settings.text = "Game";
  test_label_settings.font = font;
  test_label_settings.text_color = BLACK;
  test_label_settings.background_color = WHITE;

  ButtonSettings quit_settings;
  quit_settings.text = "Quit";
  quit_settings.font = font;
  quit_settings.text_color = WHITE;
  quit_settings.background_default_color = RED;
  quit_settings.background_clicked_color = GREEN;

  /* Create components */
  Label* test_label = new Label(20, 150, 300, 300, test_label_settings);
  Button* quit_button = new Button(20, 20, 100, 50, quit_settings);
  
  quit_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, MAIN_MENU));
  
  /* Linking the components to the screen */
  link(test_label);
  link(quit_button);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Game Music");
  Mix_PlayMusic(music, -1);
}
