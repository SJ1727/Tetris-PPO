#ifndef RESET_DATA_H
#define RESET_DATA_H

#include "app/Screens/Screen.hpp"

class ResetDataScreen : public Screen {
public:
  ResetDataScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager);
};

#endif // !RESET_DATA_H
