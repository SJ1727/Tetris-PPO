#ifndef BUTTON_H
#define BUTTON_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <string>
#include <iostream>
#include <functional>
#include <array>

#include "app/Graphics.hpp"
#include "app/WindowComponents/Label.hpp"
#include "app/WindowComponents/Animation.hpp"

typedef struct {
  std::string text = " ";
  TTF_Font* font = nullptr;
  SDL_Color textColor = BLACK;
  SDL_Color backgroundDefaultColor = TRANSPARENT;
  SDL_Color backgroundClickedColor = TRANSPARENT;
  std::array<int, 4> cornerRadius = {0, 0, 0, 0};
  Image imageDefault;
  Image imageClicked;
  
  bool textCenteredX = true;
  bool textCenteredY = true;
  int textBufferX = 5;
  int textBufferY = 5;

  Mix_Chunk *onClickSound = nullptr;
} ButtonSettings; 

class Button : public Label {
public:
  Button(int x, int y, int width, int height, ButtonSettings settings);
  ~Button() = default;
  void HandleEvents(SDL_Event* event) override;
  inline void BindClick(std::function<void()> onClick) { m_OnClick = onClick; }
  inline void BindHoverOver(std::function<void()> onHoverOver) { m_OnHoverOver = onHoverOver; }
  inline void BindHoverOff(std::function<void()> onHoverOff) { m_OnHoverOff = onHoverOff; }


private:
  SDL_Color m_BackgroundDefaultColor;
  SDL_Color m_BackgroundClickedColor;
  Image m_ImageDefault;
  Image m_ImageClicked;
  bool m_Clicked;
  bool m_Hovering;
  std::function<void()> m_OnClick;
  std::function<void()> m_OnHoverOver;
  std::function<void()> m_OnHoverOff;
  Mix_Chunk* m_OnClickSound;
};

#endif //!BUTTON_H
