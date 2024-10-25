#include "app/WindowComponents/Button.hpp"

Button::Button(int x, int y, int width, int height, ButtonSettings settings) {
  /* I HAVE NO FUCKING IDEA WHY I CANT PUT THEM HERE */
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
  m_text = settings.text;
  m_font = settings.font;
  m_text_color = settings.text_color;

  m_background_default_color = settings.background_default_color;
  // If clicked background color is not provided use the default
  m_background_clicked_color = settings. background_clicked_color;
  m_background_color = settings.background_default_color;
  
  m_image_default_surface = settings.image_default_surface;
  // If clicked image is not provided use the default
  m_image_clicked_surface = (settings.image_clicked_surface == nullptr) ? settings.image_default_surface : settings.image_clicked_surface;
  m_image_surface = settings.image_default_surface;
  
  // Alpha channel for text color must be zero otherwise will just renderer as a colored rectangle
  m_text_color.a = 0;
}

void Button::handleEvents(SDL_Event* event) {
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    float mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    bool mouse_over_button = (mouse_x > m_x && mouse_x < m_x + m_width && mouse_y > m_y && mouse_y < m_y + m_height);
    if (mouse_over_button) {
      m_on_click();
      m_background_color = m_background_clicked_color;
      m_image_surface = m_image_clicked_surface;
      m_clicked = true;
    }
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    m_background_color = m_background_default_color;
    m_image_surface = m_image_default_surface;
    m_clicked = false;
  }
}
