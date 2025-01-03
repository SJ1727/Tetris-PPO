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
#include "app/Screens/ComponentBases.hpp"

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

class ScreenManager : public std::enable_shared_from_this<ScreenManager> {
public:
  ScreenManager(int width, int height, std::shared_ptr<AppContext> context, std::shared_ptr<ResourceManager> resourceManager)
    : m_ScreenWidth(width), m_ScreenHeight(height), m_Context(context), m_ResourceManager(resourceManager) {};
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
  std::shared_ptr<ResourceManager> m_ResourceManager;
  std::unique_ptr<Screen> m_NextScreen = nullptr;
  std::unique_ptr<Screen> m_CurrentScreen = nullptr;
};

class Screen {
public:
  Screen(int width, int height, std::shared_ptr<AppContext> context) 
    : m_Width(width), m_Height(height), m_Context(context) {}
  ~Screen();

  virtual void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) = 0;
  virtual void Update();
  virtual void Render(SDL_Renderer* renderer);
  virtual void HandleEvents(SDL_Event* event);

  inline void Link(Component* component)         { m_Components.emplace_back(component); }
  inline void AddAnimation(Animation* animation) { m_Animations.emplace_back(animation); }

protected:
  inline void SetBackgroundColor(SDL_Color color) { m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, color); }

protected:
  int m_Width, m_Height;
  std::shared_ptr<AppContext> m_Context;
  std::vector<Component*> m_Components;
  std::vector<Animation*> m_Animations;
  int m_CurrentTime;
  SDL_Surface* m_BackgroundSurface;
};

#endif // !SCREEN_H
