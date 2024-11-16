#include "app/Screens/MainMenu.hpp"
#include "app/Screens/ScreenFactory.hpp"

void MainMenuScreen::loadResources() {
  m_resource_manager.loadFont("resources/font/Jersey10-Regular.ttf", 32, "Def 32");
  m_resource_manager.loadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
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

  TTF_Font* normal_font = m_resource_manager.getFont("Def 32");
  TTF_Font* title_font = m_resource_manager.getFont("Def 70");
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

  /* Create Animations */
  Animation* single_player_button_animation = animateButtonStretchLeft(single_player_button, 30, 300);
  Animation* local_multi_button_animation = animateButtonStretchLeft(local_multi_button, 30, 300);
  Animation* versus_ai_button_animation = animateButtonStretchLeft(versus_ai_button, 30, 300);
  Animation* setting_button_animation = animateButtonStretchUp(settings_button, 10, 300);
  Animation* help_button_animation = animateButtonStretchUp(help_button, 10, 300);

  /* Adding bindings to components */
  single_player_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, single_player_button_animation));
  single_player_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, single_player_button_animation));
  
  local_multi_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, local_multi_button_animation));
  local_multi_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, local_multi_button_animation));
  
  versus_ai_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, versus_ai_button_animation));
  versus_ai_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, versus_ai_button_animation));
  
  settings_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, setting_button_animation));
  settings_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, setting_button_animation));
  
  help_button->bindHoverOver(std::bind([](Animation* animation){ animation->forward(); }, help_button_animation));
  help_button->bindHoverOff(std::bind([](Animation* animation){ animation->backward(); }, help_button_animation));
  
  single_player_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, SINGLE_PLAYER_GAME));
  settings_button->bindClick(std::bind(&ScreenManager::setScreen, screen_manager, SETTINGS));

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
  
  /* Adding animations */
  addAnimation(single_player_button_animation);
  addAnimation(local_multi_button_animation);
  addAnimation(versus_ai_button_animation);
  addAnimation(setting_button_animation);
  addAnimation(help_button_animation);

  /* Starting Music */
  Mix_Music* music = m_resource_manager.getMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}

