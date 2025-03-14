#ifndef AI_SETTINGS_H
#define AI_SETTINGS_H

#include "app/Screens/Screen.hpp"

class AISettingsScreen : public Screen {
public:
  AISettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager);

  void Update() override;

private:
  TextField* m_ModelPathField;
  Label* m_tempertureValueLabel;

private:
  void Reset();
};

#endif // !AI_SETTINGS_H
