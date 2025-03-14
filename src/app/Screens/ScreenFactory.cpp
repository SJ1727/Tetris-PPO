#include "app/Screens/ScreenFactory.hpp"

std::unique_ptr<Screen> CreateScreen(int width, int height, std::shared_ptr<AppContext> context, ScreenType screenType) {
  switch (screenType) {
    case MAIN_MENU:
      return std::make_unique<MainMenuScreen>(width, height, context);
    case SETTINGS:
      return std::make_unique<SettingsScreen>(width, height, context);
    case VOLUME_SETTINGS:
      return std::make_unique<VolumeSettingsScreen>(width, height, context);
    case AI_SETTINGS:
      return std::make_unique<AISettingsScreen>(width, height, context);
    case SINGLE_PLAYER_GAME:
      return std::make_unique<SinglePlayerGameScreen>(width, height, context);
    case CONTROL_SETTINGS:
      return std::make_unique<ControlSettingsScreen>(width, height, context);
    case PLAYER_1_CONTROL_SETTINGS:
      return std::make_unique<Player1ControlSettingsScreen>(width, height, context);
    case PLAYER_2_CONTROL_SETTINGS:
      return std::make_unique<Player2ControlSettingsScreen>(width, height, context);
    case LOCAL_MULTI_PLAYER_GAME:
      return std::make_unique<LocalMultiPlayerGameScreen>(width, height, context);
    case VERSUS_AI_GAME:
      return std::make_unique<VersusAIGameScreen>(width, height, context);
    case RESET_DATA:
      return std::make_unique<ResetDataScreen>(width, height, context);
    case GAME_INFOMATION:
      return std::make_unique<GameInfomationScreen>(width, height, context);
    default:
      return nullptr;
  }
}

