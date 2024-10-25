#ifndef LABEL_H
#define LABEL_H

#include <string>
#include "app/SdlHelper.hpp"
#include "app/WindowComponents/Component.hpp"

typedef struct {
  std::string text = " ";
  TTF_Font* font = nullptr;
  SDL_Color text_color = TRANSPARENT;
  SDL_Color background_color = TRANSPARENT;
  SDL_Surface* image_surface = nullptr;
} LabelSettings; 

class Label : public Component {
public:
  Label(int x, int y, int width, int height, LabelSettings settings);
  Label() = default;
  ~Label() = default;
  void render(SDL_Renderer* renderer) override;
  void handleEvents(SDL_Event* event) override;
  inline void updateText(std::string text) { m_text = text; }

protected:
  int m_x, m_y;
  int m_width, m_height;
  std::string m_text;
  TTF_Font* m_font;
  SDL_Color m_text_color;
  SDL_Color m_background_color;
  SDL_Surface* m_image_surface;
};

#endif //!LABEL_H
