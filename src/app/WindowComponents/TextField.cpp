#include "app/WindowComponents/TextField.hpp"

TextField::TextField(int x, int y, int width, int height, TextFieldSettings settings)
  : Label (
    x, y, width, height, {
    settings.initial_text,
    settings.font,
    settings.text_color,
    settings.background_color,
    {0, 0, 0, 0},
    { nullptr, 0 , 0 },
    settings.text_centered_x,
    settings.text_centered_y,
    settings.text_buffer_x,
    settings.text_buffer_y
  }) 
{
  m_text = settings.initial_text;

  m_show_cursor = true;
  m_last_cursor_blink_milliseconds = 0;
  m_cursor_blink_milliseconds = settings.cursor_blink_milliseconds;

  m_clicked = false;
}
  
std::string TextField::getDisplayText() {
  // Adding cursor
  std::string display_text = m_text + (m_show_cursor ? "_" : " ");

  return display_text;
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
  
  m_display_text = getDisplayText();
}
