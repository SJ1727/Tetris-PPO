#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <string>
#include <iostream>
#include <functional>
#include <array>

#include "app/SdlHelper.hpp"
#include "app/WindowComponents/Label.hpp"

typedef struct {
  std::string text = " ";
  TTF_Font* font = nullptr;
  SDL_Color text_color = BLACK;
  SDL_Color background_default_color = TRANSPARENT;
  SDL_Color background_clicked_color = TRANSPARENT;
  std::array<int, 4> corner_radius = {0, 0, 0, 0};
  Image image_default;
  Image image_clicked;
  
  bool text_centered_x = true;
  bool text_centered_y = true;
  int text_buffer_x = 5;
  int text_buffer_y = 5;

  Mix_Chunk *on_click_sound = nullptr;
} ButtonSettings; 

class Button : public Label {
public:
  Button(int x, int y, int width, int height, ButtonSettings settings);
  ~Button() = default;
  void handleEvents(SDL_Event* event) override;
  inline void bindClick(std::function<void()> on_click) { m_on_click = on_click; }
  inline void bindHoverOver(std::function<void()> on_hover_over) { m_on_hover_over = on_hover_over; }
  inline void bindHoverOff(std::function<void()> on_hover_off) { m_on_hover_off = on_hover_off; }


private:
  SDL_Color m_background_default_color;
  SDL_Color m_background_clicked_color;
  Image m_image_default;
  Image m_image_clicked;
  bool m_clicked;
  bool m_hovering;
  std::function<void()> m_on_click;
  std::function<void()> m_on_hover_over;
  std::function<void()> m_on_hover_off;
  Mix_Chunk* m_on_click_sound;
};

#endif //!BUTTON_H
