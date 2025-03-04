#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"
#include "engine/TetrisEngine.hpp"
#include "app/KeyBindings.hpp"

class TetrisBoardDisplay : public Component {
public:
  TetrisBoardDisplay(int x, int y, int width, int height, TetrisEngine* tetrisEngine, KeyBindings controls);
  virtual ~TetrisBoardDisplay() = default;

  void Render(SDL_Renderer* renderer) override;
  void HandleEvents(SDL_Event* event) override;
  void Update() override;

private:
  void DrawGrid(SDL_Renderer* renderer);
  void DrawCells(SDL_Renderer* renderer);

  SDL_Color TetrominoTypeToColor(TetrominoType type);

private:
  int m_X, m_Y;
  int m_Width, m_Height;
  TetrisEngine* m_TetrisEngine;
  KeyBindings m_Controls;

  static constexpr int s_Columns = 10;
  static constexpr int s_Rows = 20;
};
