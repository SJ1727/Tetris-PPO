#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "app/Screens/Screen.hpp"
#include "app/Screens/ScreenFactory.hpp"
#include "app/AppContext.hpp"
#include "app/ResourceManager.hpp"
#include "log.hpp"

class App {
public:
  App(int width, int height);
  ~App();
  void Run();
  void ChangeScreen(Screen* screen);

private:
  void InitContext();
  void LoadResources();

private:
  int m_Width;
  int m_Height;

  std::shared_ptr<AppContext> m_Context;
  std::shared_ptr<ScreenManager> m_ScreenManager;
  std::shared_ptr<ResourceManager> m_ResourceManager;
  
  SDL_Window* m_Window;
  SDL_Renderer* m_Renderer;
};

#endif //!APP_H
