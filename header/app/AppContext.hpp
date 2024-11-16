#ifndef APP_CONTEXT_H 
#define APP_CONTEXT_H

#include "app/KeyBindings.hpp"

typedef struct {
  // Music Settings
  bool play_music;
  bool play_sound_effects;
  int music_volume;
  int sound_effects_volume;

  KeyBindings player_1_keybindings;
  KeyBindings player_2_keybindings;

} AppContext;

#endif // !APP_CONTEXT_H
