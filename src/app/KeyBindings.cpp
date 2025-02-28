#include "app/KeyBindings.hpp"

std::string KeyCodeToString(SDL_Keycode keycode) {
switch (keycode) {
  case SDLK_A: 
    return "A";
  case SDLK_B: 
    return "B";
  case SDLK_C: 
    return "C";
  case SDLK_D: 
    return "D";
  case SDLK_E: 
    return "E";
  case SDLK_F: 
    return "F";
  case SDLK_G: 
    return "G";
  case SDLK_H: 
    return "H";
  case SDLK_I: 
    return "I";
  case SDLK_J: 
    return "J";
  case SDLK_K: 
    return "K";
  case SDLK_L: 
    return "L";
  case SDLK_M: 
    return "M";
  case SDLK_N: 
    return "N";
  case SDLK_O: 
    return "O";
  case SDLK_P: 
    return "P";
  case SDLK_Q: 
    return "Q";
  case SDLK_R: 
    return "R";
  case SDLK_S: 
    return "S";
  case SDLK_T: 
    return "T";
  case SDLK_U: 
    return "U";
  case SDLK_V: 
    return "V";
  case SDLK_W: 
    return "W";
  case SDLK_X: 
    return "X";
  case SDLK_Y: 
    return "Y";
  case SDLK_Z: 
    return "Z";    
  case SDLK_0:
    return "0";
  case SDLK_1:
    return "1";
  case SDLK_2:
    return "2";
  case SDLK_3:
    return "3";
  case SDLK_4:
    return "4";
  case SDLK_5:
    return "5";
  case SDLK_6:
    return "6";
  case SDLK_7:
    return "7";
  case SDLK_8:
    return "8";
  case SDLK_9:
    return "9";
  case SDLK_UP:
    return "Up Arrow";
  case SDLK_DOWN:
    return "Down Arrow";
  case SDLK_LEFT:
    return "Left Arrow";
  case SDLK_RIGHT:
    return "Right Arrow";
  case SDLK_RSHIFT:
    return "Right Shift";
  case SDLK_LSHIFT:
    return "Left Shift";
  case SDLK_RETURN:
    return "Enter";
  case SDLK_SPACE:
    return "Space";
  default:
    return "UNKOWN";
  }
} 
