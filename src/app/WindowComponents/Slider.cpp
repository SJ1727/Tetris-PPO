#include "app/WindowComponents/Slider.hpp"

template <typename T>
Slider<T>::Slider(int x, int y, int width, int height, T* value, SliderSettings<T> settings)
  : m_X(x), m_Y(y), m_Width(width), m_Height(height), m_Value(value) {
  m_Max = settings.max;
  m_Min = settings.min;

  m_BackgroundColor = settings.backgroundColor;
  m_TrackColor = settings.trackColor;
  m_ThumbColor = settings.thumbColor;
  m_TrackPaddingX = settings.trackPaddingX;
  m_TrackPaddingY = settings.trackPaddingY;
  m_ThumbRelativeSize = settings.thumbRelativeSize;
  
  // Determing position and size of the track
  m_TrackX = m_X + m_TrackPaddingX;
  m_TrackY = m_Y + m_TrackPaddingY;
  m_TrackWidth = m_Width - 2 * m_TrackPaddingX;
  m_TrackHeight = m_Height - 2 * m_TrackPaddingY;

  // Determing position and size of thumb
  UpdateThumbPosition();
  m_ThumbWidth = m_TrackHeight + 2 * m_ThumbRelativeSize;
  m_ThumbHeight = m_TrackHeight + 2 * m_ThumbRelativeSize;
  
  m_BackgroundSurface = CreateRoundedRectangleSurface(m_Width, m_Height, settings.backgroundCornerRadius, m_BackgroundColor);
  m_TrackSurface = CreateRoundedRectangleSurface(m_TrackWidth, m_TrackHeight, settings.trackCornerRadius, m_TrackColor);
  m_ThumbSurface = CreateRoundedRectangleSurface(m_ThumbWidth, m_ThumbHeight, settings.thumbCornerRadius, m_ThumbColor);
}

template <typename T>
void Slider<T>::Render(SDL_Renderer* renderer) {
  SDL_FRect backgroundRectangle = CreateFRect(m_X, m_Y, m_Width, m_Height);
  SDL_FRect trackRectangle = CreateFRect(m_TrackX, m_TrackY, m_TrackWidth, m_TrackHeight);
  SDL_FRect thumbRectangle = CreateFRect(m_ThumbX, m_ThumbY, m_ThumbWidth, m_ThumbHeight);
  
  SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, m_BackgroundSurface); 
  SDL_Texture* trackTexture = SDL_CreateTextureFromSurface(renderer, m_TrackSurface); 
  SDL_Texture* thumbTexture = SDL_CreateTextureFromSurface(renderer, m_ThumbSurface); 
 
  SDL_RenderTexture(renderer, backgroundTexture, nullptr, &backgroundRectangle);
  SDL_RenderTexture(renderer, trackTexture, nullptr, &trackRectangle);
  SDL_RenderTexture(renderer, thumbTexture, nullptr, &thumbRectangle);
  
  SDL_DestroyTexture(backgroundTexture);
  SDL_DestroyTexture(trackTexture);
  SDL_DestroyTexture(thumbTexture);
}

template <typename T>
void Slider<T>::HandleEvents(SDL_Event* event) {
  float mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  
  bool mouseOverThumb = (mouseX > m_ThumbX && mouseX < m_ThumbX + m_ThumbWidth && mouseY > m_ThumbY && mouseY < m_ThumbY + m_ThumbHeight); 
  if (mouseOverThumb) {
    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      m_Clicked = true;
      m_ClickStartPosition = mouseX - m_ThumbPosition;
    }
  }

  if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
    m_Clicked = false;
  }

  if (m_Clicked) {
    m_ThumbPosition = mouseX - m_ClickStartPosition;
    m_ThumbPosition = std::max(0, m_ThumbPosition);
    m_ThumbPosition = std::min(m_MaxThumbPosition, m_ThumbPosition);
    m_ThumbX = m_TrackX - m_ThumbRelativeSize + m_ThumbPosition;

    *m_Value = GetValue();
  }
}

template <typename T>
void Slider<T>::Update() {
  if (!m_Clicked) {
    UpdateThumbPosition();
  }
}

template <typename T>
void Slider<T>::UpdateThumbPosition() {
  m_MaxThumbPosition = m_Width - 2 * m_TrackPaddingX - m_TrackHeight;
  float sliderProportion = (*m_Value - m_Min) / (m_Max - m_Min);
  m_ThumbPosition = m_MaxThumbPosition * sliderProportion;
  
  m_ThumbX = m_TrackX - m_ThumbRelativeSize + m_ThumbPosition;
  m_ThumbY = m_TrackY - m_ThumbRelativeSize;
}

template <typename T>
T Slider<T>::GetValue() {
  float sliderProportion = 1.0 - ((float)m_MaxThumbPosition - (float)m_ThumbPosition) / (float)m_MaxThumbPosition;
  float sliderValue = m_Min + (m_Max - m_Min) * sliderProportion;

  return static_cast<T>(sliderValue);
}

template class Slider<float>;
template class Slider<int>;
