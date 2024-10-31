#ifndef APP_CONTEXT_H 
#define APP_CONTEXT_H

typedef struct {
  // Music Settings
  bool play_music;
  bool play_sound_effects;
  int music_volume;
  int sound_effects_volume;
} AppContext;

#endif // !APP_CONTEXT_H
