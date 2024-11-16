#ifndef SINGLE_PLAYER_H
#define SINGLE_PLAYER_H

#include "app/Screens/Screen.hpp"

class SinglePlayerGameScreen : public Screen {
public:
  SinglePlayerGameScreen(int width, int height, std::shared_ptr<AppContext> context) : Screen(width, height, context) {}
  void init(ScreenManager* screen_manager) override;

protected:
  void loadResources() override;
};

#endif // !SINGLE_PLAYER_H
