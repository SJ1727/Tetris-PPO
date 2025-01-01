#ifndef VOLUME_SETTINGS_H
#define VOLUME_SETTINGS_H

#include "app/Screens/Screen.hpp"

#define DEFAULT_VOLUME 16


class VolumeSettingsScreen : public Screen {
public:
  VolumeSettingsScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void Init(ScreenManager* screenManager);

protected:
  void LoadResources() override;

private:
  static void ChangeVolume(int* volume, int newVolume);
  static void ChangeMuted(bool* volumeMuted); 
};

#endif // !VOLUME_SETTINGS_H
