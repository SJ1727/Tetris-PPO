#ifndef SINGLE_PLAYER_H
#define SINGLE_PLAYER_H

#include "app/Screens/Screen.hpp"

class SinglePlayerGameScreen : public Screen {
public:
  SinglePlayerGameScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
};

#endif // !SINGLE_PLAYER_H
