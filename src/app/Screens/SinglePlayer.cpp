#include "app/Screens/SinglePlayer.hpp"

void SinglePlayerGameScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Game Music"), -1);
}
