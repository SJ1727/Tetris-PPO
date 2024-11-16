#include "app/Screens/VolumeSettings.hpp"
#include "app/Screens/ScreenFactory.hpp"

void VolumeSettingsScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/ahronbd.ttf", 25, "Default font 25");
  m_resource_manager.loadImage("resources/images/return_icon.png", "Return Icon");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}


void VolumeSettingsScreen::init(ScreenManager* screen_manager) {
  loadResources();
  
  const SDL_Color BACKGROUND_COLOR = {19, 19, 19, 255};
  TTF_Font* normal_font = m_resource_manager.getFont("Default font 25");
  SDL_Surface* return_icon = m_resource_manager.getImage("Return Icon");
  m_background_surface = createSingleColorSurface(m_width, m_height, BACKGROUND_COLOR);
  
  /* Defining components settings */
  ButtonSettings return_button_settings;
  return_button_settings.image_default = { return_icon, 40, 40 };
  
  SliderSettings music_volume_slider_settings;
  music_volume_slider_settings.min = 0;
  music_volume_slider_settings.max = MIX_MAX_VOLUME;
  music_volume_slider_settings.starting_value = m_context->music_volume;
  music_volume_slider_settings.track_padding_x = 10;
  music_volume_slider_settings.track_padding_y = 20;
  music_volume_slider_settings.thumb_relative_size = 3;

  LabelSettings music_volume_label_settings;
  music_volume_label_settings.text = "MUSIC VOLUME";
  music_volume_label_settings.font = normal_font;
  music_volume_label_settings.text_color = WHITE;
  music_volume_label_settings.text_centered_x = false;
  
  SliderSettings sound_effects_volume_slider_settings;
  sound_effects_volume_slider_settings.min = 0;
  sound_effects_volume_slider_settings.max = MIX_MAX_VOLUME;
  sound_effects_volume_slider_settings.starting_value = m_context->sound_effects_volume;
  sound_effects_volume_slider_settings.track_padding_x = 10;
  sound_effects_volume_slider_settings.track_padding_y = 20;
  sound_effects_volume_slider_settings.thumb_relative_size = 3;

  LabelSettings sound_effects_volume_label_settings;
  sound_effects_volume_label_settings.text = "SOUND FX VOLUME";
  sound_effects_volume_label_settings.font = normal_font;
  sound_effects_volume_label_settings.text_color = WHITE;
  sound_effects_volume_label_settings.text_centered_x = false;
  
  /* Create components */
  Button* return_button = new Button(20, 530, 50, 50, return_button_settings);
  Slider* music_volume_slider = new Slider(260, 18, 200, 50, music_volume_slider_settings); 
  Label* music_volume_label = new Label(20, 20, 200, 50, music_volume_label_settings);
  Slider* sound_effects_volume_slider = new Slider(260, 68, 200, 50, sound_effects_volume_slider_settings); 
  Label* sound_effects_volume_label = new Label(20, 70, 250, 50, sound_effects_volume_label_settings);

  return_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));

  music_volume_slider->bind(std::bind(
    [](std::shared_ptr<AppContext> context, float volume) { 
      context->music_volume = (int)volume;
    }, m_context, std::placeholders::_1));
  
  sound_effects_volume_slider->bind(std::bind(
    [](std::shared_ptr<AppContext> context, float volume) { 
      context->sound_effects_volume = (int)volume;
    }, m_context, std::placeholders::_1));
  
  /* Linking the components to the screen */
  link(return_button);
  link(music_volume_slider);
  link(music_volume_label);
  link(sound_effects_volume_slider);
  link(sound_effects_volume_label);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
