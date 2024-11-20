#ifndef AI_SETTINGS_H
#define AI_SETTINGS_H

#include "app/Screens/Screen.hpp"

class AISettingsScreen : public Screen {
public:
  AISettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(ScreenManager* screenManager);

protected:
  void LoadResources() override;
};

#endif // !AI_SETTINGS_H
