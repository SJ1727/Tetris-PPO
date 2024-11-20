#ifndef APP_CONTEXT_H 
#define APP_CONTEXT_H

#include "app/KeyBindings.hpp"

typedef struct {
  // Music Settings
  bool playMusic;
  bool playSoundEffects;
  int musicVolume;
  int soundEffectsVolume;

  KeyBindings player1Keybindings;
  KeyBindings player2Keybindings;

} AppContext;

#endif // !APP_CONTEXT_H
