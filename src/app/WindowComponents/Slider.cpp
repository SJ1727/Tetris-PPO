#include "app/WindowComponents/Slider.hpp"

Slider::Slider(int x, int y, int width, int height, SliderSettings settings)
  : m_x(x), m_y(y), m_width(width), m_height(height) {
  m_max = settings.max;
  m_min = settings.min;

  m_background_color = settings.background_color;
  m_track_color = settings.track_color;
  m_thumb_color = settings.thumb_color;
  m_track_padding_x = settings.track_padding_x;
  m_track_padding_y = settings.track_padding_y;
  m_thumb_relative_size = settings.thumb_relative_size;
  
  // Determing position and size of the track
  m_track_x = m_x + m_track_padding_x;
  m_track_y = m_y + m_track_padding_y;
  m_track_width = m_width - 2 * m_track_padding_x;
  m_track_height = m_height - 2 * m_track_padding_y;

  // Determing max and starting position of the thumb
  m_max_thumb_position = m_width - 2 * m_track_padding_x - m_track_height;
  float slider_proportion = (settings.starting_value - m_min) / (m_max - m_min);
  m_thumb_position = m_max_thumb_position * slider_proportion;

  // Determing position and size of thumb
  m_thumb_x = m_track_x - m_thumb_relative_size + m_thumb_position;
  m_thumb_y = m_track_y - m_thumb_relative_size;
  m_thumb_width = m_track_height + 2 * m_thumb_relative_size;
  m_thumb_height = m_track_height + 2 * m_thumb_relative_size;
}

void Slider::bind(std::function<void(float)> on_value_change) {
  m_on_value_change = on_value_change;
  m_on_value_change(getValue());
}

void Slider::render(SDL_Renderer* renderer) {
  m_thumb_x = m_track_x - m_thumb_relative_size + m_thumb_position;
  
  SDL_FRect slider_rectangle = createFRect(m_x, m_y, m_width, m_height);
  SDL_FRect track_rectangle = createFRect(m_track_x, m_track_y, m_track_width, m_track_height);
  SDL_FRect thumb_rectangle = createFRect(m_thumb_x, m_thumb_y, m_thumb_width, m_thumb_height);

  SDL_SetRenderDrawColor(renderer, m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a);
  SDL_RenderFillRect(renderer, &slider_rectangle);
  SDL_SetRenderDrawColor(renderer, m_track_color.r, m_track_color.g, m_track_color.b, m_track_color.a);
  SDL_RenderFillRect(renderer, &track_rectangle);
  SDL_SetRenderDrawColor(renderer, m_thumb_color.r, m_thumb_color.g, m_thumb_color.b, m_thumb_color.a);
  SDL_RenderFillRect(renderer, &thumb_rectangle);
}

void Slider::handleEvents(SDL_Event* event) {
  float mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  
  bool mouse_over_thumb = (mouse_x > m_thumb_x && mouse_x < m_thumb_x + m_thumb_width && mouse_y > m_thumb_y && mouse_y < m_thumb_y + m_thumb_height); 
  if (mouse_over_thumb) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      m_clicked = true;
      m_click_start_position = mouse_x - m_thumb_position;
    }
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    m_clicked = false;
  }

  if (m_clicked) {
    m_thumb_position = mouse_x - m_click_start_position;
    m_thumb_position = std::max(0, m_thumb_position);
    m_thumb_position = std::min(m_max_thumb_position, m_thumb_position);

    m_on_value_change(getValue());
  }
}

float Slider::getValue() {
  float slider_proportion = 1.0 - ((float)m_max_thumb_position - (float)m_thumb_position) / (float)m_max_thumb_position;
  float slider_value = m_min + (m_max - m_min) * slider_proportion;

  return slider_value;
}
