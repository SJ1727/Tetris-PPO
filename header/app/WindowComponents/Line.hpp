#ifndef LINE_H
#define LINE_H


#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"

class Line : public Component {
public:
  Line(int x1, int y1, int x2, int y2, SDL_Color color);
  ~Line() = default;
  void render(SDL_Renderer* renderer) override;
  void handleEvents(SDL_Event* event) override {}

private:
  int m_x1, m_x2, m_y1, m_y2;
  SDL_Color m_color;
};

#endif // !LINE_H
