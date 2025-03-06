#ifndef APP_CONTEXT_H 
#define APP_CONTEXT_H

#include "app/KeyBindings.hpp"
#include "engine/TetrisEngine.hpp"

#define APP_MAX_VOLUME 16

typedef struct {
  // Music Settings
  bool playMaster;
  bool playMusic;
  bool playSoundEffects;
  int masterVolume;
  int musicVolume;
  int soundEffectsVolume;

  int highScore;
  int mostLinesCleared;
  float timePlayedSeconds;

  KeyBindings player1KeyBindings;
  KeyBindings player2KeyBindings;

  TetrisEngine* singlePlayerEngine;
  TetrisEngine* localPlayer1Engine;
  TetrisEngine* localPlayer2Engine;
  TetrisEngine* versusPlayerEngine;
  TetrisEngine* aiPlayerEngine;

} AppContext;

#endif // !APP_CONTEXT_H
