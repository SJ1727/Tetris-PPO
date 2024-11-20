#ifndef PLAYER_1_CONTROL_SETTINGS_H
#define PLAYER_1_CONTROL_SETTINGS_H

#include "app/Screens/Screen.hpp"

class Player1ControlSettingsScreen : public Screen {
public:
  Player1ControlSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(ScreenManager* screenManager) override;

protected:
  void LoadResources() override;
};

#endif // !PLAYER_1_CONTROL_SETTINGS_H
