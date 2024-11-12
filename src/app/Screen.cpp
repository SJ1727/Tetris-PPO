#include "app/Screen.hpp"

std::unique_ptr<Screen> createScreen(int width, int height, std::shared_ptr<AppContext> context, ScreenType screen_type) {
  switch (screen_type) {
    case MAIN_MENU:
      return std::make_unique<MainMenuScreen>(width, height, context);
    case SETTINGS:
      return std::make_unique<SettingsScreen>(width, height, context);
    case VOLUME_SETTINGS:
      return std::make_unique<VolumeSettingsScreen>(width, height, context);
    case AI_SETTINGS:
      return std::make_unique<AISettingsScreen>(width, height, context);
    case SINGLE_PLAYER_GAME:
      return std::make_unique<SinglePlayerGameScreen>(width, height, context);
  }

  return nullptr;
}

/*
 *  --- Screen Manager ---  
 */

void ScreenManager::setScreen(ScreenType screen_type) {
  m_next_screen = createScreen(m_screen_width, m_screen_height, m_context, screen_type);
}

void ScreenManager::switchScreen() {
  // Waits for any sound effects to finish playing
  while (Mix_Playing(-1)) { }

  if (m_next_screen != nullptr) {
    m_current_screen = std::move(m_next_screen);
    m_current_screen->init(this);
    m_next_screen = nullptr;
  }
}

void ScreenManager::update() {
  if (m_current_screen) {
    m_current_screen->update();
  }
  
  switchScreen();
}

void ScreenManager::render(SDL_Renderer* renderer) {
  if (m_current_screen) {
    m_current_screen->render(renderer);
  }
}

void ScreenManager::handleEvents(SDL_Event* event) {
  if (m_current_screen) {
    m_current_screen->handleEvents(event);
  }
}

/*
 *  --- Screen ---  
 */

Screen::~Screen() {
  for (auto& component : m_components) {
    delete component;
  }

  m_components.clear();
  Mix_HaltMusic();
}

void Screen::render(SDL_Renderer* renderer) {
  SDL_FRect background_rectangle = createFRect(0, 0, m_width, m_height); 
  SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, m_background_surface);
  SDL_RenderTexture(renderer, background_texture, nullptr, &background_rectangle);
  SDL_DestroyTexture(background_texture);
  
  for (auto& component : m_components) {
    component->render(renderer);
  }
}

void Screen::handleEvents(SDL_Event* event) {
  for (auto& component : m_components) {
    component->handleEvents(event);
  }
}

void Screen::update() {
  for (auto& component : m_components) {
    component->update();
  }

  // Control the volume and playing of music
  if (Mix_VolumeMusic(-1) != 0 && !m_context->play_music) {
    Mix_VolumeMusic(0);
  } else {
    Mix_VolumeMusic(m_context->music_volume);
  }

  // Control the volume and playing of sound effects
  if (Mix_Volume(-1, -1) != 0 && !m_context->play_sound_effects) {
    Mix_Volume(-1, 0);
  } else {
    Mix_Volume(-1, m_context->sound_effects_volume);
  }
}

/*
 *  --- Main Menu Screen ---  
 */

void MainMenuScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/Jersey10-Regular.ttf", 32, "Default font 32");
  m_resource_manager.loadFont("resources/font/Jersey10-Regular.ttf", 70, "Default font 70");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
  m_resource_manager.loadImage("resources/images/settings_icon.png", "Settings Icon");
  m_resource_manager.loadImage("resources/images/question_mark.png", "Question Mark");
  m_resource_manager.loadSoundEffect("resources/sound/Click1.wav", "Button Click");
}

void MainMenuScreen::init(ScreenManager* screen_manager) {
  loadResources();

  const SDL_Color BACKGROUND_COLOR = { 22, 22, 22, 255 };
  const SDL_Color BUTTON_COLOR = { 76, 75, 75, 255 };
  const SDL_Color LABEL_COLOR = { 51, 51, 51, 255 };

  TTF_Font* normal_font = m_resource_manager.getFont("Default font 32");
  TTF_Font* title_font = m_resource_manager.getFont("Default font 70");
  SDL_Surface* settings_icon = m_resource_manager.getImage("Settings Icon");
  SDL_Surface* help_icon = m_resource_manager.getImage("Question Mark");
  Mix_Chunk* button_click = m_resource_manager.getSoundEffect("Button Click");
  m_background_surface = createSingleColorSurface(m_width, m_height, BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings title_text_settings;
  title_text_settings.text = "Tetris";
  title_text_settings.font = title_font;
  title_text_settings.text_color = WHITE;
  title_text_settings.background_color = TRANSPARENT;

  ButtonSettings single_player_button_settings;
  single_player_button_settings.text = "Single Player";
  single_player_button_settings.font = normal_font;
  single_player_button_settings.text_color = WHITE;
  single_player_button_settings.background_default_color = BUTTON_COLOR;
  single_player_button_settings.corner_radius = { 20, 0, 20, 0 };
  
  ButtonSettings local_multi_button_settings;
  local_multi_button_settings.text = "Local Multiplayer";
  local_multi_button_settings.font = normal_font;
  local_multi_button_settings.text_color = WHITE;
  local_multi_button_settings.background_default_color = BUTTON_COLOR;
  local_multi_button_settings.corner_radius = { 20, 0, 20, 0 };
  
  ButtonSettings versus_ai_button_settings;
  versus_ai_button_settings.text = "Player vs AI";
  versus_ai_button_settings.font = normal_font;
  versus_ai_button_settings.text_color = WHITE;
  versus_ai_button_settings.background_default_color = BUTTON_COLOR;
  versus_ai_button_settings.corner_radius = { 20, 0, 20, 0 };

  ButtonSettings settings_button_settings;
  settings_button_settings.image_default = { settings_icon, 40, 40 };
  settings_button_settings.background_default_color = BUTTON_COLOR;
  settings_button_settings.corner_radius = { 20, 20, 0, 0 };
  settings_button_settings.on_click_sound = button_click;

  ButtonSettings help_button_settings;
  help_button_settings.image_default = { help_icon, 40, 40 };
  help_button_settings.background_default_color = BUTTON_COLOR;
  help_button_settings.corner_radius = { 20, 20, 0, 0 };
  help_button_settings.on_click_sound = button_click;

  LabelSettings game_infomation_background_settings;
  game_infomation_background_settings.background_color = LABEL_COLOR;
  game_infomation_background_settings.corner_radius = { 0, 20, 0, 20 };
  
  LabelSettings high_score_label_settings;
  high_score_label_settings.text = "High Score";
  high_score_label_settings.font = normal_font;
  high_score_label_settings.text_color = WHITE;
  
  LabelSettings high_score_number_label_settings;
  high_score_number_label_settings.text = "xxx";
  high_score_number_label_settings.font = normal_font;
  high_score_number_label_settings.text_color = WHITE;
  
  LabelSettings most_lines_label_settings;
  most_lines_label_settings.text = "Most Lines Cleared";
  most_lines_label_settings.font = normal_font;
  most_lines_label_settings.text_color = WHITE;
  
  LabelSettings most_lines_number_label_settings;
  most_lines_number_label_settings.text = "xxx";
  most_lines_number_label_settings.font = normal_font;
  most_lines_number_label_settings.text_color = WHITE;
  
  LabelSettings time_played_label_settings;
  time_played_label_settings.text = "Hours Played";
  time_played_label_settings.font = normal_font;
  time_played_label_settings.text_color = WHITE;
  
  LabelSettings time_played_number_label_settings;
  time_played_number_label_settings.text = "xxx";
  time_played_number_label_settings.font = normal_font;
  time_played_number_label_settings.text_color = WHITE;

  /* Create components */
  Label* title_text = new Label(528, 10, 100, 100, title_text_settings);

  Button* single_player_button = new Button(440, 140, 360, 80, single_player_button_settings); 
  Button* local_multi_button = new Button(440, 260, 360, 80, local_multi_button_settings); 
  Button* versus_ai_button = new Button(440, 380, 360, 80, versus_ai_button_settings); 
  
  Button* settings_button = new Button(480, 520, 80, 80, settings_button_settings); 
  Button* help_button = new Button(640, 520, 80, 80, help_button_settings); 

  Label* game_infomation_background = new Label(0, 50, 280, 500, game_infomation_background_settings);
  Line* game_infomation_line_1 = new Line(0, 206, 280, 206, BACKGROUND_COLOR);
  Line* game_infomation_line_2 = new Line(0, 374, 280, 374, BACKGROUND_COLOR);
  Label* high_score_label = new Label(68, 60, 122, 34, high_score_label_settings);
  Label* high_score_number_label = new Label(108, 124, 42, 34, high_score_number_label_settings);
  Label* most_lines_label = new Label(34, 216, 204, 34, most_lines_label_settings);
  Label* most_lines_number_label = new Label(108, 284, 42, 34, most_lines_number_label_settings);
  Label* time_played_label = new Label(58, 384, 146, 34, time_played_label_settings);
  Label* time_played_number_label = new Label(108, 446, 42, 34, time_played_number_label_settings);



  single_player_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SINGLE_PLAYER_GAME));
  settings_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));

  /* Linking the components to the screen */
  link(title_text);
  link(single_player_button);
  link(local_multi_button);
  link(versus_ai_button);
  link(settings_button);
  link(help_button);
  link(game_infomation_background);
  link(game_infomation_line_1);
  link(game_infomation_line_2);
  link(high_score_label);
  link(high_score_number_label);
  link(most_lines_label);
  link(most_lines_number_label);
  link(time_played_label);
  link(time_played_number_label);

  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}

/*
 *  --- Volume Settings Screen ---  
 */

void SettingsScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/ahronbd.ttf", 25, "Normal");
  m_resource_manager.loadImage("resources/images/return_icon.png", "Return Icon");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}

void SettingsScreen::init(ScreenManager* screen_manager) {
  loadResources();

  const SDL_Color BACKGROUND_COLOR = {19, 19, 19, 255};
  TTF_Font* normal_font = m_resource_manager.getFont("Normal");
  SDL_Surface* return_icon = m_resource_manager.getImage("Return Icon");
  m_background_surface = createSingleColorSurface(m_width, m_height, BACKGROUND_COLOR);

  
  /* Defining components settings */
  ButtonSettings return_button_settings;
  return_button_settings.image_default = { return_icon, 40, 40 };
  
  ButtonSettings volume_button_settings;
  volume_button_settings.text = "Volume Settings";
  volume_button_settings.font = normal_font;
  volume_button_settings.text_color = WHITE;
  volume_button_settings.background_default_color = BLACK;
  
  ButtonSettings ai_button_settings;
  ai_button_settings.text = "AI Settings";
  ai_button_settings.font = normal_font;
  ai_button_settings.text_color = WHITE;
  ai_button_settings.background_default_color = BLACK;
  ai_button_settings.corner_radius[0] = 5;
  ai_button_settings.corner_radius[1] = 5;
  
  Button* return_button = new Button(20, 530, 50, 50, return_button_settings);
  Button* volume_button = new Button(20, 20, 250, 60, volume_button_settings); 
  Button* ai_button = new Button(20, 100, 250, 60, ai_button_settings); 
  
  return_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, MAIN_MENU));

  volume_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, VOLUME_SETTINGS));
  
  ai_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, AI_SETTINGS));
  
  /* Linking the components to the screen */
  link(return_button);
  link(volume_button);
  link(ai_button);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}

/*
 *  --- Volume Settings Screen ---  
 */

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

  return_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));

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

/*
 *  --- AI Settings Screen ---  
 */

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
  
  return_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));
  
  /* Linking the components to the screen */
  link(return_button);
  link(model_path_label);
  link(model_path_field);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}

/*
 *  --- Single Player Game Screen ---  
 */

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
  
  quit_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, MAIN_MENU));
  
  /* Linking the components to the screen */
  link(test_label);
  link(quit_button);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Game Music");
  Mix_PlayMusic(music, -1);
}
