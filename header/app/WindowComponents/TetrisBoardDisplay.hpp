#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"
#include "engine/TetrisEngine.hpp"
#include "app/KeyBindings.hpp"

#define FRAME_RATE 60
#define FRAME_DELAY (1000 / FRAME_RATE)

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

  Uint32 m_FrameStart;
};
