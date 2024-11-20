#include "app/Screens/Screen.hpp"
#include "app/Screens/ScreenFactory.hpp"

/* Animation functions */
Animation* AnimateButtonStretchLeft(Button* button, int distance, int duration) {
  return new Animation(
    std::bind(
    [](Button* button, int x, int width, int distance, int duration, int time){
      float normilizedTime = (float) time / duration;
      int distanceTravelled = EaseInOut(normilizedTime) * distance;
      button->UpdatePositionX(x - distanceTravelled);
      button->UpdateWidth(width + distanceTravelled);
    },
    button,
    button->GetPositionX(),
    button->GetWidth(),
    distance,
    duration,
    std::placeholders::_1
  ), duration
  );
}

Animation* AnimateButtonStretchRight(Button* button, int distance, int duration) {
  return new Animation(
    std::bind(
    [](Button* button, int width, int distance, int duration, int time){
      float normilizedTime = (float) time / duration;
      int distanceTravelled = EaseInOut(normilizedTime) * distance;
      button->UpdateWidth(width + distanceTravelled);
    },
    button,
    button->GetWidth(),
    distance,
    duration,
    std::placeholders::_1
  ), duration
  );
}

Animation* AnimateButtonStretchUp(Button* button, int distance, int duration) {
  return new Animation(
    std::bind(
    [](Button* button, int y, int height, int distance, int duration, int time){
      float normilizedTime = (float) time / duration;
      int distanceTravelled = EaseInOut(normilizedTime) * distance;
      button->UpdatePositionY(y - distanceTravelled);
      button->UpdateHeight(height + distanceTravelled);
    },
    button,
    button->GetPositionY(),
    button->GetHeight(),
    distance,
    duration,
    std::placeholders::_1
  ), duration
  );
}

/*
 *  --- Screen Manager ---  
 */

void ScreenManager::SetScreen(ScreenType screenType) {
  m_NextScreen = CreateScreen(m_ScreenWidth, m_ScreenHeight, m_Context, screenType);
}

void ScreenManager::SwitchScreen() {
  // Waits for any sound effects to finish playing
  while (Mix_Playing(-1)) { }

  if (m_NextScreen != nullptr) {
    m_CurrentScreen = std::move(m_NextScreen);
    m_CurrentScreen->Init(this);
    m_NextScreen = nullptr;
  }
}

void ScreenManager::Update() {
  if (m_CurrentScreen) {
    m_CurrentScreen->Update();
  }
  
  SwitchScreen();
}

void ScreenManager::Render(SDL_Renderer* renderer) {
  if (m_CurrentScreen) {
    m_CurrentScreen->Render(renderer);
  }
}

void ScreenManager::HandleEvents(SDL_Event* event) {
  if (m_CurrentScreen) {
    m_CurrentScreen->HandleEvents(event);
  }
}

/*
 *  --- Screen ---  
 */

Screen::~Screen() {
  for (auto& component : m_Components) {
    delete component;
  }
  
  for (auto& animation : m_Animations) {
    delete animation;
  }

  m_Components.clear();
  Mix_HaltMusic();
}

void Screen::Render(SDL_Renderer* renderer) {
  SDL_FRect backgroundRectangle = CreateFRect(0, 0, m_Width, m_Height); 
  SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, m_BackgroundSurface);
  SDL_RenderTexture(renderer, backgroundTexture, nullptr, &backgroundRectangle);
  SDL_DestroyTexture(backgroundTexture);
  
  for (auto& component : m_Components) {
    component->Render(renderer);
  }
}

void Screen::HandleEvents(SDL_Event* event) {
  for (auto& component : m_Components) {
    component->HandleEvents(event);
  }
}

void Screen::Update() {
  for (auto& component : m_Components) {
    component->Update();
  }

  for (auto& animation : m_Animations) {
    animation->Step(SDL_GetTicks() - m_CurrentTime);
  }
  m_CurrentTime = SDL_GetTicks();

  // Control the volume and playing of music
  if (Mix_VolumeMusic(-1) != 0 && !m_Context->playMusic) {
    Mix_VolumeMusic(0);
  } else {
    Mix_VolumeMusic(m_Context->musicVolume);
  }

  // Control the volume and playing of sound effects
  if (Mix_Volume(-1, -1) != 0 && !m_Context->playSoundEffects) {
    Mix_Volume(-1, 0);
  } else {
    Mix_Volume(-1, m_Context->soundEffectsVolume);
  }
}
