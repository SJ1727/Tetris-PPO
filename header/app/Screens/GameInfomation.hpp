#ifndef GAME_INFOMATION_H
#define GAME_INFOMATION_H

#include "app/Screens/Screen.hpp"

class GameInfomationScreen : public Screen {
public:
  GameInfomationScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager);
};

#endif // !GAME_INFOMATION_H
