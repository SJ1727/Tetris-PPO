#include "app/Screens/Settings.hpp"
#include "app/Screens/ScreenFactory.hpp"

void SettingsScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/Jersey10-Regular.ttf", 32, "Def 32");
  m_resource_manager.loadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
  m_resource_manager.loadImage("resources/images/return_icon.png", "Return Icon");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}

void SettingsScreen::init(ScreenManager* screen_manager) {
  loadResources();

  const SDL_Color BACKGROUND_COLOR = { 22, 22, 22, 255 };
  const SDL_Color BUTTON_COLOR = { 76, 75, 75, 255 };
  const SDL_Color LABEL_COLOR = { 51, 51, 51, 255 };

  TTF_Font* title_font = m_resource_manager.getFont("Def 70");
  TTF_Font* normal_font = m_resource_manager.getFont("Def 32");
  SDL_Surface* return_icon = m_resource_manager.getImage("Return Icon");
  m_background_surface = createSingleColorSurface(m_width, m_height, BACKGROUND_COLOR);

  
  /* Defining components settings */
  LabelSettings title_text_settings;
  title_text_settings.text = "Settings";
  title_text_settings.font = title_font;
  title_text_settings.text_color = WHITE;
  title_text_settings.background_color = TRANSPARENT;
  
  ButtonSettings return_button_settings;
  return_button_settings.image_default = { return_icon, 40, 40 };
  return_button_settings.background_default_color = BUTTON_COLOR;
  return_button_settings.corner_radius = { 20, 20, 0, 0 };
  
  ButtonSettings volume_button_settings;
  volume_button_settings.text = "Volume";
  volume_button_settings.font = normal_font;
  volume_button_settings.text_color = WHITE;
  volume_button_settings.background_default_color = BUTTON_COLOR;
  volume_button_settings.corner_radius = { 20, 0, 20, 0 };
  
  ButtonSettings control_button_settings;
  control_button_settings.text = "Controls";
  control_button_settings.font = normal_font;
  control_button_settings.text_color = WHITE;
  control_button_settings.background_default_color = BUTTON_COLOR;
  control_button_settings.corner_radius = { 20, 0, 20, 0 };
  
  ButtonSettings ai_button_settings;
  ai_button_settings.text = "AI Player";
  ai_button_settings.font = normal_font;
  ai_button_settings.text_color = WHITE;
  ai_button_settings.background_default_color = BUTTON_COLOR;
  ai_button_settings.corner_radius = { 20, 0, 20, 0 };
  
  ButtonSettings reset_data_button_settings;
  reset_data_button_settings.text = "Reset Data";
  reset_data_button_settings.font = normal_font;
  reset_data_button_settings.text_color = WHITE;
  reset_data_button_settings.background_default_color = BUTTON_COLOR;
  reset_data_button_settings.corner_radius = { 0, 20, 0, 20 };
  
  /* Create components */
  Label* title_text = new Label(528, 10, 100, 100, title_text_settings);
  
  Button* return_button = new Button(640, 520, 80, 80, return_button_settings); 
  
  Button* volume_button = new Button(440, 140, 360, 80, volume_button_settings); 
  Button* control_button = new Button(440, 260, 360, 80, control_button_settings); 
  Button* ai_button = new Button(440, 380, 360, 80, ai_button_settings); 
  Button* reset_data_button = new Button(0, 140, 360, 80, reset_data_button_settings); 
  
  /* Create Animations */
  Animation* return_button_animation = animateButtonStretchUp(return_button, 10, 300);
  Animation* volume_button_animation = animateButtonStretchLeft(volume_button, 30, 300);
  Animation* control_button_animation = animateButtonStretchLeft(control_button, 30, 300);
  Animation* ai_button_animation = animateButtonStretchLeft(ai_button, 30, 300);
  Animation* reset_data_button_animation = animateButtonStretchRight(reset_data_button, 30, 300);

  /* Adding bindings to components */
  return_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, return_button_animation));
  return_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, return_button_animation));
  
  volume_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, volume_button_animation));
  volume_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, volume_button_animation));
  
  control_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, control_button_animation));
  control_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, control_button_animation));
  
  ai_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, ai_button_animation));
  ai_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, ai_button_animation));
  
  reset_data_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, reset_data_button_animation));
  reset_data_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, reset_data_button_animation));
  
  return_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, MAIN_MENU));

  volume_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, VOLUME_SETTINGS));
  ai_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, AI_SETTINGS));
  
  /* Linking the components to the screen */
  link(title_text);
  link(return_button);
  link(volume_button);
  link(control_button);
  link(ai_button);
  link(reset_data_button);
  
  /* Adding animations */
  addAnimation(return_button_animation);
  addAnimation(volume_button_animation);
  addAnimation(control_button_animation);
  addAnimation(ai_button_animation);
  addAnimation(reset_data_button_animation);

  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
