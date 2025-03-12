#include "app/WindowComponents/TextField.hpp"

TextField::TextField(int x, int y, int width, int height, TextFieldSettings settings)
  : Label (
    x, y, width, height, {
    settings.initialText,
    settings.font,
    settings.textColor,
    settings.backgroundColor,
    settings.cornerRadius,
    { nullptr, 0 , 0 },
    settings.textCenteredX,
    settings.textCenteredY,
    settings.textBufferX,
    settings.textBufferY
  }) 
{
  m_Text = settings.initialText;

  m_ShowCursor = true;
  m_LastCursorBlinkMilliseconds = 0;
  m_CursorBlinkMilliseconds = settings.cursorBlinkMilliseconds;

  m_Clicked = false;
}
  
std::string TextField::GetDisplayText() {
  // Adding cursor
  std::string displayText = m_Text + (m_ShowCursor ? "_" : " ");

  return displayText;
}

void TextField::HandleEvents(SDL_Event* event) {
  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    m_Clicked = (mouseX > m_X && mouseX < m_X + m_Width && mouseY > m_Y && mouseY < m_Y + m_Height);
  }
  
  if (m_Clicked) {
    switch (event->type) {
      // Adding characters to text
      case SDL_EVENT_TEXT_INPUT:
        m_Text += event->text.text;
        break;
     
      case SDL_EVENT_KEY_DOWN:
        // Handles backspace
        if (event->key.key == SDLK_BACKSPACE && m_Text.length() > 0) {
          m_Text = m_Text.substr(0, m_Text.length() - 1);
        }

        // Handles pasting
        if (event->key.key == SDLK_V && event->key.mod == SDL_KMOD_LCTRL) {
          std::string clipboardText = SDL_GetClipboardText();
          m_Text += clipboardText;
        }
        break;
    } 
  }
}

void TextField::Update() {
  // Makes the cursor blink
  if (m_Clicked) {
    int currentTime = SDL_GetTicks();
    if (currentTime - m_LastCursorBlinkMilliseconds > m_CursorBlinkMilliseconds) {
      m_ShowCursor = !m_ShowCursor;
      m_LastCursorBlinkMilliseconds = currentTime;
    }
  } else {
    m_ShowCursor = false;
  } 
  
  m_DisplayText = GetDisplayText();
}
