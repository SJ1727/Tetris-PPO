#ifndef KEY_BINDINGS_H
#define KEY_BINDINGS_H

#include <string>

#include <SDL3/SDL.h>

typedef struct {
  SDL_Keycode right;
  SDL_Keycode left;
  SDL_Keycode down;
  SDL_Keycode rotateRight;
  SDL_Keycode rotateLeft;
  SDL_Keycode drop;
  SDL_Keycode hold;
} KeyBindings;

std::string KeyCodeToString(SDL_Keycode keycode); 

#endif // !KEY_BINDINGS_H
