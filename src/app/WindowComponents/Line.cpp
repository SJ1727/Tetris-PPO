#include "app/WindowComponents/Line.hpp"

Line::Line(int x1, int y1, int x2, int y2, SDL_Color color) 
  : m_X1(x1), m_Y1(y1), m_X2(x2), m_Y2(y2), m_Color(color) {

}

void Line::Render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Color.a);
  SDL_RenderLine(renderer, m_X1, m_Y1, m_X2, m_Y2);
}
