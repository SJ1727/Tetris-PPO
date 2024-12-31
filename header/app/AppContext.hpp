#ifndef APP_CONTEXT_H 
#define APP_CONTEXT_H

#include "app/KeyBindings.hpp"

#define APP_MAX_VOLUME 16

typedef struct {
  // Music Settings
  bool playMaster;
  bool playMusic;
  bool playSoundEffects;
  int masterVolume;
  int musicVolume;
  int soundEffectsVolume;

  KeyBindings player1Keybindings;
  KeyBindings player2Keybindings;

} AppContext;

#endif // !APP_CONTEXT_H
