#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"
#include "engine/TetrisEngine.hpp"
#include "app/KeyBindings.hpp"

class TetrisBoardDisplay : public Component {
public:
  TetrisBoardDisplay(int x, int y, int width, int height, TetrisEngine* tetrisEngine, KeyBindings controls);
  virtual ~TetrisBoardDisplay();

  void Render(SDL_Renderer* renderer) override;
  void HandleEvents(SDL_Event* event) override;

private:
  void DrawGrid(SDL_Renderer* renderer);

private:
  int m_X, m_Y;
  int m_Width, m_Height;
  TetrisEngine* m_TetrisEngine;
  KeyBindings m_Controls;
}
