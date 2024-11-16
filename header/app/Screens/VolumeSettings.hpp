#ifndef VOLUME_SETTINGS_H
#define VOLUME_SETTINGS_H

#include "app/Screens/Screen.hpp"

class VolumeSettingsScreen : public Screen {
public:
  VolumeSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager);

protected:
  void loadResources() override;
};

#endif // !VOLUME_SETTINGS_H
