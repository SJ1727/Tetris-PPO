#include "app/WindowComponents/TextField.hpp"

TextField::TextField(int x, int y, int width, int height, TextFieldSettings settings)
  : m_x(x), m_y(y), m_width(width), m_height(height) {
  m_text = settings.initial_text;
  m_font = settings.font;
  m_text_color = settings.text_color;
  m_background_color = settings.background_color;
  m_text_centered_x = settings.text_centered_x;
  m_text_centered_y = settings.text_centered_y;
  m_text_buffer_x = settings.text_buffer_x;
  m_text_buffer_y = settings.text_buffer_y;

  m_show_cursor = true;
  m_last_cursor_blink_milliseconds = 0;
  m_cursor_blink_milliseconds = settings.cursor_blink_milliseconds;

  m_clicked = false;

  // Alpha channel for text color must be zero otherwise will just renderer as a colored rectangle
  m_text_color.a = 0;
}
  
std::string TextField::getDisplayText() {
  // Adding cursor
  std::string display_text = m_text + (m_show_cursor ? "_" : " ");

  return display_text;
}

void TextField::render(SDL_Renderer* renderer) {
  int text_x, text_y, text_width, text_height;
  SDL_FRect label_rectangle = createFRect(m_x, m_y, m_width, m_height);
  
  // Renders background with one solid color
  SDL_SetRenderDrawColor(renderer, m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a);
  SDL_RenderFillRect(renderer, &label_rectangle);
  
  SDL_Texture* text_texture = createTextTexture(renderer, getDisplayText(), m_font, m_text_color);
    
  // Calculate position of text rectangle
  text_x = m_x + (m_text_centered_x ? (m_width - text_texture->w) / 2 : m_text_buffer_x);
  text_y = m_y + (m_text_centered_y ? (m_height - text_texture->h) / 2 : m_text_buffer_y);
  text_width = m_width - 2 * (text_x - m_x);
  text_height = m_height - 2 * (text_y - m_y);

  int text_rectangle_width = text_texture->w > text_width ? text_width : text_texture->w;
  int clipping_x = text_texture->w > text_width ? text_texture->w - text_width : 0;

  // Rendering Text
  SDL_FRect text_rectangle = createFRect(text_x, text_y, text_rectangle_width, text_texture->h);
  SDL_FRect clipping_rectangle = createFRect(clipping_x, 0, text_rectangle_width, text_texture->h);
  SDL_RenderTexture(renderer, text_texture, &clipping_rectangle, &text_rectangle);
  SDL_DestroyTexture(text_texture);
}

void TextField::handleEvents(SDL_Event* event) {
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    float mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    m_clicked = (mouse_x > m_x && mouse_x < m_x + m_width && mouse_y > m_y && mouse_y < m_y + m_height);
  }
  
  if (m_clicked) {
    switch (event->type) {
      // Adding characters to text
      case SDL_EVENT_TEXT_INPUT:
        m_text += event->text.text;
        break;
     
      case SDL_EVENT_KEY_DOWN:
        // Handles backspace
        if (event->key.key == SDLK_BACKSPACE && m_text.length() > 0) {
          m_text = m_text.substr(0, m_text.length() - 1);
        }

        // Handles pasting
        if (event->key.key == SDLK_V && event->key.mod == SDL_KMOD_LCTRL) {
          std::string clipboard_text = SDL_GetClipboardText();
          m_text += clipboard_text;
        }
        break;
    } 
  }
}

void TextField::update() {
  // Makes the cursor blink
  if (m_clicked) {
    int current_time = SDL_GetTicks();
    if (current_time - m_last_cursor_blink_milliseconds > m_cursor_blink_milliseconds) {
      m_show_cursor = !m_show_cursor;
      m_last_cursor_blink_milliseconds = current_time;
    }
  } else {
    m_show_cursor = false;
  } 
}
