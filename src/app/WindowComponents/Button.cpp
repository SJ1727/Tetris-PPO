#include "app/WindowComponents/Button.hpp"

Button::Button(int x, int y, int width, int height, ButtonSettings settings) 
  : Label (
    x, y, width, height, {
    settings.text,
    settings.font,
    settings.text_color,
    settings.background_default_color,
    settings.corner_radius,
    settings.image_default,
    settings.text_centered_x,
    settings.text_centered_y,
    settings.text_buffer_x,
    settings.text_buffer_y
  })
{
  m_background_default_color = settings.background_default_color;
  // If clicked background color is not provided use the default
  m_background_clicked_color = settings. background_clicked_color;
  
  m_image_default = settings.image_default;
  // If clicked image is not provided use the default
  m_image_clicked = (settings.image_clicked.surface == nullptr) ? settings.image_default : settings.image_clicked;

  m_on_click_sound = settings.on_click_sound;
}

void Button::handleEvents(SDL_Event* event) {
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    float mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    bool mouse_over_button = (mouse_x > m_x && mouse_x < m_x + m_width && mouse_y > m_y && mouse_y < m_y + m_height);
    if (mouse_over_button) {
      m_clicked = true;
      if (m_on_click) { m_on_click(); }

      // Change the button appearance
      m_background_color = m_background_clicked_color;
      m_image = m_image_clicked;

      // Plays clicked sounded effect
      if (m_on_click_sound != nullptr) {
        Mix_PlayChannel(-1, m_on_click_sound, 0);
      }
    }
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    m_clicked = false;
    
    // Change the button appearance
    m_background_color = m_background_default_color;
    m_image = m_image_default;
  }
}
