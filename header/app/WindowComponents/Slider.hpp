#ifndef SLIDER_H
#define SLIDER_H

#include <string>
#include <algorithm>
#include <functional>
#include <array>
#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"

template <typename T>
struct SliderSettings {
  T min, max; // Min and Max value that the slider will return
  SDL_Color backgroundColor = TRANSPARENT;
  SDL_Color trackColor = GRAY;
  SDL_Color thumbColor = WHITE;
  int trackPaddingX;
  int trackPaddingY;
  int thumbRelativeSize; // Size of the thumb relative to the track

  std::array<int, 4> backgroundCornerRadius = { 0, 0, 0, 0 };
  std::array<int, 4> trackCornerRadius = { 0, 0, 0, 0 };
  std::array<int, 4> thumbCornerRadius = { 0, 0, 0, 0 };
}; 

template <typename T>
class Slider : public Component {
public:
  Slider(int x, int y, int width, int height, T* value, SliderSettings<T> settings);
  ~Slider() = default;
  void Render(SDL_Renderer* renderer) override;
  void HandleEvents(SDL_Event* event) override;
  void Update() override;

private:
  T GetValue();
  void UpdateThumbPosition();

private:
  int m_X, m_Y;
  int m_Width, m_Height;
  float m_Min, m_Max;
  SDL_Color m_BackgroundColor;
  SDL_Color m_TrackColor;
  SDL_Color m_ThumbColor;
  int m_TrackPaddingX;
  int m_TrackPaddingY;
  int m_ThumbRelativeSize;
  int m_MaxThumbPosition;
  int m_ThumbPosition;

  int m_TrackX;
  int m_TrackY;
  int m_TrackWidth;
  int m_TrackHeight;
  int m_ThumbX;
  int m_ThumbY;
  int m_ThumbWidth;
  int m_ThumbHeight;

  SDL_Surface* m_BackgroundSurface;
  SDL_Surface* m_TrackSurface;
  SDL_Surface* m_ThumbSurface;

  T* m_Value;

  bool m_Clicked = false;
  int m_ClickStartPosition;
};

#endif //!SLIDER_H
