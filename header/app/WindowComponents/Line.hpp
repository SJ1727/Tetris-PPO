#ifndef LINE_H
#define LINE_H


#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"

class Line : public Component {
public:
  Line(int x1, int y1, int x2, int y2, SDL_Color color);
  ~Line() = default;
  void Render(SDL_Renderer* renderer) override;
  void HandleEvents(SDL_Event* event) override {}

private:
  int m_X1, m_X2, m_Y1, m_Y2;
  SDL_Color m_Color;
};

#endif // !LINE_H
