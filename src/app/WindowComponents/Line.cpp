#include "app/WindowComponents/Line.hpp"

Line::Line(int x1, int y1, int x2, int y2, SDL_Color color) 
  : m_x1(x1), m_y1(y1), m_x2(x2), m_y2(y2), m_color(color) {

}

void Line::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
  SDL_RenderLine(renderer, m_x1, m_y1, m_x2, m_y2);
}
