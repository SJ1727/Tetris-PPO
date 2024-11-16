#ifndef SETTINGS_H
#define SETTINGS_H

#include "app/Screens/Screen.hpp"

class SettingsScreen : public Screen {
public:
  SettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager) override;

protected:
  void loadResources() override;
};

#endif // !SETTINGS_H
