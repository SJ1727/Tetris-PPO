#ifndef PLAYER_TETRIS_BOARD_DISPLAY_H
#define PLAYER_TETRIS_BOARD_DISPLAY_H

#include "app/WindowComponents/TetrisBoardDisplay.hpp"

class PlayerTetrisBoardDisplay : public TetrisBoardDisplay {
public:
  PlayerTetrisBoardDisplay(int x, int y, int width, int height, TetrisEngine* tetrisEngine, KeyBindings controls);
  ~PlayerTetrisBoardDisplay() = default;
    
  void HandleEvents(SDL_Event* event) override;

private:
  KeyBindings m_Controls;
};

#endif // !PLAYER_TETRIS_BOARD_DISPLAY_H
