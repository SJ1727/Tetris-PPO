#include "app/Screens/Screen.hpp"
#include "app/Screens/ScreenFactory.hpp"

/* Animation functions */
Animation* animateButtonStretchLeft(Button* button, int distance, int duration) {
  return new Animation(
    std::bind(
    [](Button* button, int x, int width, int distance, int duration, int time){
      float normilized_time = (float) time / duration;
      int distance_travelled = easeInOut(normilized_time) * distance;
      button->updatePositionX(x - distance_travelled);
      button->updateWidth(width + distance_travelled);
    },
    button,
    button->getPositionX(),
    button->getWidth(),
    distance,
    duration,
    std::placeholders::_1
  ), duration
  );
}

Animation* animateButtonStretchRight(Button* button, int distance, int duration) {
  return new Animation(
    std::bind(
    [](Button* button, int width, int distance, int duration, int time){
      float normilized_time = (float) time / duration;
      int distance_travelled = easeInOut(normilized_time) * distance;
      button->updateWidth(width + distance_travelled);
    },
    button,
    button->getWidth(),
    distance,
    duration,
    std::placeholders::_1
  ), duration
  );
}

Animation* animateButtonStretchUp(Button* button, int distance, int duration) {
  return new Animation(
    std::bind(
    [](Button* button, int y, int height, int distance, int duration, int time){
      float normilized_time = (float) time / duration;
      int distance_travelled = easeInOut(normilized_time) * distance;
      button->updatePositionY(y - distance_travelled);
      button->updateHeight(height + distance_travelled);
    },
    button,
    button->getPositionY(),
    button->getHeight(),
    distance,
    duration,
    std::placeholders::_1
  ), duration
  );
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
  
  for (auto& animation : m_animations) {
    delete animation;
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

  for (auto& animation : m_animations) {
    animation->step(SDL_GetTicks() - m_current_time);
  }
  m_current_time = SDL_GetTicks();

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
