#ifndef APP_H
#define APP_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <ostream>
#include <iostream>
#include "app/Screen.hpp"
#include "app/AppContext.hpp"

class App {
public:
  App(int width, int height);
  ~App();
  void run();
  void changeScreen(Screen* screen);

private:
  int m_width;
  int m_height;
  ScreenManager* m_screen_manager;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};

#endif //!APP_H
