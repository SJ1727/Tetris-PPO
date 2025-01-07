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
    m_CurrentScreen->Init(shared_from_this(), m_ResourceManager);
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
  for (auto& pair : m_ComponentMap) {
    delete pair.second;
  }
  
  for (auto& pair : m_AnimationMap) {
    delete pair.second;
  }

  Mix_HaltMusic();
}

void Screen::Render(SDL_Renderer* renderer) {
  SDL_FRect backgroundRectangle = CreateFRect(0, 0, m_Width, m_Height); 
  SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, m_BackgroundSurface);
  SDL_RenderTexture(renderer, backgroundTexture, nullptr, &backgroundRectangle);
  SDL_DestroyTexture(backgroundTexture);
  
  for (auto& pair : m_ComponentMap) {
    pair.second->Render(renderer);
  }
}

void Screen::HandleEvents(SDL_Event* event) {
  for (auto& pair : m_ComponentMap) {
    pair.second->HandleEvents(event);
  }
}

void Screen::Update() {
  // Updating all the components on the screen
  for (auto& pair : m_ComponentMap) {
    pair.second->Update();
  }

  // Plays the Animations
  for (auto& pair : m_AnimationMap) {
    pair.second->Step(SDL_GetTicks() - m_CurrentTime);
  }
  m_CurrentTime = SDL_GetTicks();

  // Control the volume and playing of music
  if (!m_Context->playMusic || !m_Context->playMaster) {
    Mix_VolumeMusic(0);
  } else {
    Mix_VolumeMusic(m_Context->musicVolume * m_Context->masterVolume);
  }

  // Control the volume and playing of sound effects
  if (!m_Context->playSoundEffects || !m_Context->playMaster) {
    Mix_Volume(-1, 0);
  } else {
    Mix_Volume(-1, m_Context->soundEffectsVolume * m_Context->masterVolume);
  }
}
  
void Screen::Link(Component* component, std::string alias="") {
  if (m_ComponentMap.find(alias) != m_ComponentMap.end()) {
    LOG_WARN("Cannot link two components with the same alias of \"" + alias + "\"");
    return;
  }

  m_ComponentMap[alias] = component;
}

void Screen::Link(Animation* animation, std::string alias="") {
  if (m_AnimationMap.find(alias) != m_AnimationMap.end()) {
    LOG_WARN("Cannot link two animations with the same alias of \"" + alias + "\"");
    return;
  }

  m_AnimationMap[alias] = animation;
}

Component* Screen::GetComponent(std::string alias)  {
  if (m_ComponentMap.find(alias) != m_ComponentMap.end()) {
    return m_ComponentMap[alias];
  }
  
  LOG_WARN("Component with alias \"" + alias + "\" has not been linked");
  return nullptr;

}

Animation* Screen::GetAnimation(std::string alias) {
  if (m_AnimationMap.find(alias) != m_AnimationMap.end()) {
    return m_AnimationMap[alias];
  }
  
  LOG_WARN("Animation with alias \"" + alias + "\" has not been linked");
  return nullptr;
}
