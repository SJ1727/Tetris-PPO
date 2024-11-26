#ifndef SCREEN_H 
#define SCREEN_H

#include <vector>
#include <functional>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "app/ResourceManager.hpp"
#include "app/AppContext.hpp"
#include "app/WindowComponents/WindowComponents.hpp"

enum ScreenType {
  MAIN_MENU,
  SETTINGS,
  VOLUME_SETTINGS,
  AI_SETTINGS,
  SINGLE_PLAYER_GAME,
  CONTROL_SETTINGS,
  PLAYER_1_CONTROL_SETTINGS,
  PLAYER_2_CONTROL_SETTINGS
};

class Screen;
class ScreenManager;

Animation* AnimateButtonStretchLeft(Button* button, int distance, int duration);
Animation* AnimateButtonStretchRight(Button* button, int distance, int duration);
Animation* AnimateButtonStretchUp(Button* button, int distance, int duration);

class ScreenManager {
public:
  ScreenManager(int width, int height, std::shared_ptr<AppContext> context)
    : m_ScreenWidth(width), m_ScreenHeight(height), m_Context(context) {};
  ~ScreenManager() = default;

  void SetScreen(ScreenType screenType);
  void Update();
  void Render(SDL_Renderer* renderer);
  void HandleEvents(SDL_Event* event);

private:
  void SwitchScreen();

private:
  int m_ScreenWidth, m_ScreenHeight;
  std::shared_ptr<AppContext> m_Context;
  std::unique_ptr<Screen> m_NextScreen = nullptr;
  std::unique_ptr<Screen> m_CurrentScreen = nullptr;
};

class Screen {
public:
  Screen(int width, int height, std::shared_ptr<AppContext> context) 
    : m_ResourceManager(), m_Width(width), m_Height(height), m_Context(context) {}
  ~Screen();

  virtual void Init(ScreenManager* screenManager) = 0;
  void Update();
  void Render(SDL_Renderer* renderer);
  void HandleEvents(SDL_Event* event);

  inline void Link(Component* component)         { m_Components.emplace_back(component); }
  inline void AddAnimation(Animation* animation) { m_Animations.emplace_back(animation); }

protected:
  virtual void LoadResources() = 0;

protected:
  int m_Width, m_Height;
  std::shared_ptr<AppContext> m_Context;
  ResourceManager m_ResourceManager;
  ScreenManager* m_screenManager;
  std::vector<Component*> m_Components;
  std::vector<Animation*> m_Animations;
  int m_CurrentTime;
  SDL_Surface* m_BackgroundSurface;
};

#endif // !SCREEN_H
