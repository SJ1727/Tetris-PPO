#ifndef LOCAL_MULTI_PLAYER_H
#define LOCAL_MULTI_PLAYER_H

#include "app/Screens/Screen.hpp"

class LocalMultiPlayerGameScreen : public Screen {
public:
  LocalMultiPlayerGameScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
  
  void Update() override;

private:
  void UpdateNextTetrominoLabel();
  void UpdateHeldTetrominoLabel();
  void UpdateGameStatisticsLabel();
  Image TetrominoTypeToImage(TetrominoType type);

private:
  Label* m_HeldTetrominoLabel1;
  Label* m_HeldTetrominoLabel2;
  Label* m_NextTetrominoLabel1;
  Label* m_NextTetrominoLabel2;
  Label* m_scoreLabel1;
  Label* m_scoreLabel2;
  Label* m_linesClearedLabel1;
  Label* m_linesClearedLabel2;
  Label* m_levelLabel1;
  Label* m_levelLabel2;

  Image m_ITetromino;
  Image m_JTetromino;
  Image m_LTetromino;
  Image m_OTetromino;
  Image m_STetromino;
  Image m_TTetromino;
  Image m_ZTetromino;
};

#endif // !LOCAL_MULTI_PLAYER_H
