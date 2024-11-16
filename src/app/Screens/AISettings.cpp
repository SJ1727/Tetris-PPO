#include "app/Screens/AISettings.hpp"
#include "app/Screens/ScreenFactory.hpp"

void AISettingsScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/ahronbd.ttf", 25, "Default font 25");
  m_resource_manager.loadFont("resources/font/JetBrainsMonoNerdFont-Medium.ttf", 15, "Text field");
  m_resource_manager.loadImage("resources/images/return_icon.png", "Return Icon");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}

void AISettingsScreen::init(ScreenManager* screen_manager) {
  loadResources();
  
  const SDL_Color BACKGROUND_COLOR = {19, 19, 19, 255};
  TTF_Font* normal_font = m_resource_manager.getFont("Default font 25");
  TTF_Font* text_field_font = m_resource_manager.getFont("Text field");
  SDL_Surface* return_icon = m_resource_manager.getImage("Return Icon");
  m_background_surface = createSingleColorSurface(m_width, m_height, BACKGROUND_COLOR);
  
  /* Defining components settings */
  ButtonSettings return_button_settings;
  return_button_settings.image_default = { return_icon, 40, 40 };
  
  LabelSettings model_path_label_settings;
  model_path_label_settings.text = "MODEL PATH";
  model_path_label_settings.font = normal_font;
  model_path_label_settings.text_color = WHITE;
  model_path_label_settings.text_centered_x = false;
  
  TextFieldSettings model_path_field_settings;
  model_path_field_settings.initial_text = "example/path/model.onnx";
  model_path_field_settings.font = text_field_font;
  
  /* Create components */
  Button* return_button = new Button(20, 530, 50, 50, return_button_settings);
  Label* model_path_label = new Label(20, 20, 200, 50, model_path_label_settings);
  TextField* model_path_field = new TextField(190, 30, 400, 25, model_path_field_settings);
  
  return_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));
  
  /* Linking the components to the screen */
  link(return_button);
  link(model_path_label);
  link(model_path_field);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
