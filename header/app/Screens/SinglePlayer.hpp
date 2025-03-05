#ifndef SINGLE_PLAYER_H
#define SINGLE_PLAYER_H

#include "app/Screens/Screen.hpp"

class SinglePlayerGameScreen : public Screen {
public:
  SinglePlayerGameScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
  
  void Update() override;

private:
  void UpdateNextTetrominoLabel();
  void UpdateHeldTetrominoLabel();

private:
  Label* m_HeldTetrominoLabel;
  Label* m_NextTetrominoLabel;
  Label* m_scoreLabel;
  Label* m_linesClearedLabel;
  Label* m_levelLabel;

  Image m_ITetromino;
  Image m_JTetromino;
  Image m_LTetromino;
  Image m_OTetromino;
  Image m_STetromino;
  Image m_TTetromino;
  Image m_ZTetromino;
};

#endif // !SINGLE_PLAYER_H
