#ifndef CONTROL_SETTINGS_H
#define CONTROL_SETTINGS_H

#include "app/Screens/Screen.hpp"

class ControlSettingsScreen : public Screen {
public:
  ControlSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
};

#endif // !CONTROL_SETTINGS_H
