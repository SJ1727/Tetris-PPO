#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "app/Screens/Screen.hpp"

class MainMenuScreen : public Screen {
public:
  MainMenuScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
};

#endif // !MAIN_MENU_H
