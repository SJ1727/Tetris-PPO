#ifndef PLAYER_2_CONTROL_SETTINGS_H
#define PLAYER_2_CONTROL_SETTINGS_H

#include "app/Screens/Screen.hpp"

class Player2ControlSettingsScreen : public Screen {
public:
  Player2ControlSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;
};

#endif // !PLAYER_2_CONTROL_SETTINGS_H
