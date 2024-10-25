#include "app/Screen.hpp"

std::unique_ptr<Screen> createScreen(int width, int height, std::shared_ptr<AppContext> context, ScreenType screen_type) {
  switch (screen_type) {
    case MAIN_MENU:
      return std::make_unique<MainMenuScreen>(width, height, context);
    case SETTINGS:
      return std::make_unique<SettingsScreen>(width, height, context);
    case VOLUME_SETTINGS:
      return std::make_unique<VolumeSettingsScreen>(width, height, context);
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
  if (!Mix_PausedMusic() && !m_context->play_music) {
    Mix_PauseMusic();
  }

  if (Mix_PausedMusic() && m_context->play_music) {
    Mix_ResumeMusic();
  }

  Mix_VolumeMusic(m_context->music_volume);
}

/*
 *  --- Main Menu Screen ---  
 */

void MainMenuScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/ahronbd.ttf", 12, "Default font 12");
  m_resource_manager.loadFont("resources/font/ahronbd.ttf", 50, "Default font 50");
  m_resource_manager.loadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
  m_resource_manager.loadImage("resources/images/Logo.png", "Title");
  m_resource_manager.loadImage("resources/images/settings_icon.png", "Settings Icon");
}

void MainMenuScreen::init(ScreenManager* screen_manager) {
  loadResources();

  const SDL_Color BACKGROUND_COLOR = {19, 19, 19, 255};
  TTF_Font* normal_font = m_resource_manager.getFont("Default font 12");
  TTF_Font* title_font = m_resource_manager.getFont("Default font 50");
  SDL_Surface* title = m_resource_manager.getImage("Title");
  SDL_Surface* settings_icon = m_resource_manager.getImage("Settings Icon");
  m_background_surface = createSingleColorSurface(m_width, m_height, BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings title_image_settings;
  title_image_settings.image_surface = title;

  LabelSettings title_text_settings;
  title_text_settings.text = "Tetris";
  title_text_settings.font = title_font;
  title_text_settings.text_color = WHITE;
  title_text_settings.background_color = TRANSPARENT;

  ButtonSettings start_settings;
  start_settings.text = "Single Player";
  start_settings.font = normal_font;
  start_settings.text_color = WHITE;
  start_settings.background_default_color = BLACK;

  ButtonSettings music_settings;
  music_settings.text = "Mute";
  music_settings.font = normal_font;
  music_settings.text_color = WHITE;
  music_settings.background_default_color = BLACK;
  music_settings.background_clicked_color = GREEN;

  ButtonSettings settings_button_settings;
  settings_button_settings.image_default_surface = settings_icon;

  /* Create components */
  Button* start_button = new Button(320, 250, 100, 50, start_settings); 
  Button* music_button = new Button(320, 350, 100, 50, music_settings); 
  Button* settings_button = new Button(320, 450, 50, 50, settings_button_settings); 
  Label* title_text = new Label(365, 20, 100, 100, title_text_settings);
  Label* title_image = new Label(235, 20, 110, 100, title_image_settings);
  
  start_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SINGLE_PLAYER_GAME));

  settings_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));

  music_button->bind(std::bind(
    [](std::shared_ptr<AppContext> context) {
      context->play_music = !context->play_music;
    }, m_context));

  /* Linking the components to the screen */
  m_components.emplace_back(start_button);
  m_components.emplace_back(music_button);
  m_components.emplace_back(settings_button);
  m_components.emplace_back(title_text);
  m_components.emplace_back(title_image);

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
  return_button_settings.image_default_surface = return_icon;
  
  ButtonSettings volume_button_settings;
  volume_button_settings.text = "Volume Settings";
  volume_button_settings.font = normal_font;
  volume_button_settings.text_color = WHITE;
  volume_button_settings.background_default_color = BLACK;
  
  Button* return_button = new Button(20, 530, 50, 50, return_button_settings);
  Button* volume_button = new Button(20, 20, 250, 60, volume_button_settings); 
  
  return_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, MAIN_MENU));

  volume_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, VOLUME_SETTINGS));
  
  /* Linking the components to the screen */
  m_components.emplace_back(return_button);
  m_components.emplace_back(volume_button);
  
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
  return_button_settings.image_default_surface = return_icon;
  
  SliderSettings volume_slider_settings;
  volume_slider_settings.min = 0;
  volume_slider_settings.max = MIX_MAX_VOLUME;
  volume_slider_settings.starting_value = m_context->music_volume;
  volume_slider_settings.track_padding_x = 10;
  volume_slider_settings.track_padding_y = 20;
  volume_slider_settings.thumb_relative_size = 3;

  LabelSettings volume_label_settings;
  volume_label_settings.text = "VOLUME";
  volume_label_settings.font = normal_font;
  volume_label_settings.text_color = WHITE;
  
  /* Create components */
  Button* return_button = new Button(20, 530, 50, 50, return_button_settings);
  Slider* volume_slider = new Slider(140, 18, 200, 50, volume_slider_settings); 
  Label* volume_label = new Label(20, 20, 100, 50, volume_label_settings);
  return_button->bind(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));

  volume_slider->bind(std::bind(
    [](std::shared_ptr<AppContext> context, float volume) { 
      context->music_volume = (int)volume;
    }, m_context, std::placeholders::_1));
 
  /* Linking the components to the screen */
  m_components.emplace_back(return_button);
  m_components.emplace_back(volume_slider);
  m_components.emplace_back(volume_label);
  
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
  m_components.emplace_back(test_label);
  m_components.emplace_back(quit_button);
  
  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Game Music");
  Mix_PlayMusic(music, -1);
}

