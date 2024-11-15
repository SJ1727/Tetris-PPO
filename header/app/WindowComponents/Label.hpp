#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <algorithm>
#include <array>

#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"
#include "app/WindowComponents/Image.hpp"

typedef struct {
  std::string text = " ";
  TTF_Font* font = nullptr;
  SDL_Color text_color = TRANSPARENT;
  SDL_Color background_color = TRANSPARENT;
  std::array<int, 4> corner_radius = {0, 0, 0, 0};
  Image image;
  
  bool text_centered_x = true;
  bool text_centered_y = true;
  int text_buffer_x = 5;
  int text_buffer_y = 5;
} LabelSettings; 

class Label : public Component {
public:
  Label(int x, int y, int width, int height, LabelSettings settings);
  virtual ~Label() = default;
  void render(SDL_Renderer* renderer) override;
  void handleEvents(SDL_Event* event) override;
  
  inline void updateText(std::string text) { m_display_text = text; }
  inline void updatePositionX(int x) { m_x = x; }
  inline void updatePositionY(int y) { m_y = y; }
  inline void updateWidth(int width) { m_width = width; }
  inline void updateHeight(int height) { m_height = height; }
  inline int getPositionX() { return m_x; }
  inline int getPositionY() { return m_y; }
  inline int getWidth() { return m_width; }
  inline int getHeight() { return m_height; }

protected:
  int m_x, m_y;
  int m_width, m_height;
  std::string m_display_text;
  TTF_Font* m_font;
  SDL_Color m_text_color;
  SDL_Color m_background_color;
  std::array<int, 4> m_corner_radius;
  SDL_Surface* m_background_surface;
  Image m_image;
  
  bool m_text_centered_x;
  bool m_text_centered_y;
  int m_text_buffer_x;
  int m_text_buffer_y;
};

#endif //!LABEL_H
