#ifndef SLIDER_H
#define SLIDER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "app/SdlHelper.hpp"
#include "app/WindowComponents/Component.hpp"

typedef struct {
  float min, max; // Min and Max value that the slider will return
  float starting_value;
  SDL_Color background_color = TRANSPARENT;
  SDL_Color track_color = GRAY;
  SDL_Color thumb_color = WHITE;
  int track_padding_x;
  int track_padding_y;
  int thumb_relative_size; // Size of the thumb relative to the track
} SliderSettings; 

class Slider : public Component {
public:
  Slider(int x, int y, int width, int height, SliderSettings settings);
  ~Slider() = default;
  void bind(std::function<void(float)> on_value_change);
  void render(SDL_Renderer* renderer) override;
  void handleEvents(SDL_Event* event) override;

private:
  float getValue();

private:
  int m_x, m_y;
  int m_width, m_height;
  float m_min, m_max;
  SDL_Color m_background_color;
  SDL_Color m_track_color;
  SDL_Color m_thumb_color;
  int m_track_padding_x;
  int m_track_padding_y;
  int m_thumb_relative_size;
  int m_max_thumb_position;
  int m_thumb_position;

  int m_track_x;
  int m_track_y;
  int m_track_width;
  int m_track_height;
  int m_thumb_x;
  int m_thumb_y;
  int m_thumb_width;
  int m_thumb_height;

  std::function<void(float)> m_on_value_change;

  bool m_clicked = false;
  int m_click_start_position;
};

#endif //!SLIDER_H
