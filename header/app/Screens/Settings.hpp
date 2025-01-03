#ifndef SETTINGS_H
#define SETTINGS_H

#include "app/Screens/Screen.hpp"

class SettingsScreen : public Screen {
public:
  SettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
};

#endif // !SETTINGS_H
