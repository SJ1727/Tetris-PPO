#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <iostream>
#include <functional>
#include "app/SdlHelper.hpp"
#include "app/WindowComponents/Label.hpp"

typedef struct {
  std::string text = " ";
  TTF_Font* font = nullptr;
  SDL_Color text_color = BLACK;
  SDL_Color background_default_color = TRANSPARENT;
  SDL_Color background_clicked_color = TRANSPARENT;
  SDL_Surface* image_default_surface = nullptr;
  SDL_Surface* image_clicked_surface = nullptr;
} ButtonSettings; 

class Button : public Label {
public:
  Button(int x, int y, int width, int height, ButtonSettings settings);
  ~Button() = default;
  void handleEvents(SDL_Event* event) override;
  inline void bind(std::function<void()> on_click) { m_on_click = on_click; }

private:
  SDL_Color m_background_default_color;
  SDL_Color m_background_clicked_color;
  SDL_Surface* m_image_default_surface;
  SDL_Surface* m_image_clicked_surface;
  bool m_clicked;
  std::function<void()> m_on_click;
};

#endif //!BUTTON_H
