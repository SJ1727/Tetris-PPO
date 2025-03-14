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
#include "app/Screens/LocalMultiPlayer.hpp"
#include "app/Screens/VersusAI.hpp"
#include "app/Screens/ResetData.hpp"
#include "app/Screens/GameInfomation.hpp"
#include <memory>

std::unique_ptr<Screen> CreateScreen(int width, int height, std::shared_ptr<AppContext> context, ScreenType screenType);

#endif // !SCREEN_FACTORY_H
