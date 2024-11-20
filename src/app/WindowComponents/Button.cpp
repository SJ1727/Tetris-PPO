#include "app/WindowComponents/Button.hpp"

Button::Button(int x, int y, int width, int height, ButtonSettings settings) 
  : Label (
    x, y, width, height, {
    settings.text,
    settings.font,
    settings.textColor,
    settings.backgroundDefaultColor,
    settings.cornerRadius,
    settings.imageDefault,
    settings.textCenteredX,
    settings.textCenteredY,
    settings.textBufferX,
    settings.textBufferY
  })
{
  m_BackgroundDefaultColor = settings.backgroundDefaultColor;
  // If clicked background color is not provided use the default
  m_BackgroundClickedColor = settings. backgroundClickedColor;
  
  m_ImageDefault = settings.imageDefault;
  // If clicked image is not provided use the default
  m_ImageClicked = (settings.imageClicked.surface == nullptr) ? settings.imageDefault : settings.imageClicked;

  m_OnClickSound = settings.onClickSound;
}

void Button::HandleEvents(SDL_Event* event) {
  float mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  
  bool hovering = (mouseX > m_X && mouseX < m_X + m_Width && mouseY > m_Y && mouseY < m_Y + m_Height);
  if (hovering && !m_Hovering && m_OnHoverOver) { m_OnHoverOver(); }
  if (!hovering && m_Hovering && m_OnHoverOff) { m_OnHoverOff(); }
  m_Hovering = hovering;

  if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

    if (m_Hovering) {
      m_Clicked = true;
      if (m_OnClick) { m_OnClick(); }

      // Change the button appearance
      m_BackgroundColor = m_BackgroundClickedColor;
      m_Image = m_ImageClicked;

      // Plays clicked sounded effect
      if (m_OnClickSound != nullptr) {
        Mix_PlayChannel(-1, m_OnClickSound, 0);
      }
    }
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    m_Clicked = false;
    
    // Change the button appearance
    m_BackgroundColor = m_BackgroundDefaultColor;
    m_Image = m_ImageDefault;
  }
}
