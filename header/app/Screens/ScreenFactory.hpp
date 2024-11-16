#ifndef SCREEN_FACTORY_H
#define SCREEN_FACTORY_H

#include "app/Screens/Screen.hpp"
#include "app/Screens/MainMenu.hpp"
#include "app/Screens/Settings.hpp"
#include "app/Screens/VolumeSettings.hpp"
#include "app/Screens/AISettings.hpp"
#include "app/Screens/SinglePlayer.hpp"
#include "app/Screens/ControlSettings.hpp"
#include "app/Screens/Player1ControlSettings.hpp"
#include "app/Screens/Player2ControlSettings.hpp"
#include <memory>

std::unique_ptr<Screen> createScreen(int width, int height, std::shared_ptr<AppContext> context, ScreenType screen_type);

#endif // !SCREEN_FACTORY_H
