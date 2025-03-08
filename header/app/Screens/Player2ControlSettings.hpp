#ifndef PLAYER_2_CONTROL_SETTINGS_H
#define PLAYER_2_CONTROL_SETTINGS_H

#include "app/Screens/Screen.hpp"

class Player2ControlSettingsScreen : public Screen {
public:
  Player2ControlSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) override;

  void Update() override;
  void HandleEvents(SDL_Event* event) override;
  

private:
  enum KeyCommand { HOLD, DOWN, RIGHT, LEFT, DROP, ROTATE_RIGHT, ROTATE_LEFT, NONE };

  KeyCommand m_CurrentCommandToSwitch;

  Button* m_HoldBindButton;
  Button* m_DownBindButton;
  Button* m_RightBindButton;
  Button* m_LeftBindButton;
  Button* m_DropBindButton;
  Button* m_RotCWBindButton;
  Button* m_RotACWBindButton;
};

#endif // !PLAYER_2_CONTROL_SETTINGS_H
