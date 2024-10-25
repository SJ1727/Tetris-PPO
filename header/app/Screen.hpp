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

class Screen;
class ScreenManager;

enum ScreenType {
  MAIN_MENU,
  SETTINGS,
  VOLUME_SETTINGS,
  SINGLE_PLAYER_GAME
};

std::unique_ptr<Screen> createScreen(int width, int height, std::shared_ptr<AppContext> context, ScreenType screen_type);

class ScreenManager {
public:
  ScreenManager(int width, int height, std::shared_ptr<AppContext> context)
    : m_screen_width(width), m_screen_height(height), m_context(context) {};
  ~ScreenManager() = default;
  void setScreen(ScreenType screen_type);
  void update();
  void render(SDL_Renderer* renderer);
  void handleEvents(SDL_Event* event);

private:
  void switchScreen();

private:
  int m_screen_width, m_screen_height;
  std::shared_ptr<AppContext> m_context;
  std::unique_ptr<Screen> m_next_screen = nullptr;
  std::unique_ptr<Screen> m_current_screen = nullptr;
};

class Screen {
public:
  Screen(int width, int height, std::shared_ptr<AppContext> context) 
    : m_resource_manager(), m_width(width), m_height(height), m_context(context) {}
  ~Screen();
  virtual void init(ScreenManager* screen_manager) = 0;
  void update();
  void render(SDL_Renderer* renderer);
  void handleEvents(SDL_Event* event);

protected:
  virtual void loadResources() = 0;

protected:
  int m_width, m_height;
  std::shared_ptr<AppContext> m_context;
  ResourceManager m_resource_manager;
  ScreenManager* m_screen_manager;
  std::vector<Component*> m_components;
  SDL_Surface* m_background_surface;
};

class MainMenuScreen : public Screen {
public:
  MainMenuScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager) override;

protected:
  void loadResources() override;
};

class SettingsScreen : public Screen {
public:
  SettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager) override;

protected:
  void loadResources() override;
};

class VolumeSettingsScreen : public Screen {
public:
  VolumeSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager);

protected:
  void loadResources() override;
};

class SinglePlayerGameScreen : public Screen {
public:
  SinglePlayerGameScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager) override;

protected:
  void loadResources() override;
};

#endif // !SCREEN_H
