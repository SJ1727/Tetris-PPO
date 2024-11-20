#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <algorithm>
#include <array>

#include "app/Graphics.hpp"
#include "app/WindowComponents/Component.hpp"
#include "app/WindowComponents/Image.hpp"

typedef struct {
  std::string text = " ";
  TTF_Font* font = nullptr;
  SDL_Color textColor = TRANSPARENT;
  SDL_Color backgroundColor = TRANSPARENT;
  std::array<int, 4> cornerRadius = {0, 0, 0, 0};
  Image image;
  
  bool textCenteredX = true;
  bool textCenteredY = true;
  int textBufferX = 5;
  int textBufferY = 5;
} LabelSettings; 

class Label : public Component {
public:
  Label(int x, int y, int width, int height, LabelSettings settings);
  virtual ~Label() = default;
  void Render(SDL_Renderer* renderer) override;
  void HandleEvents(SDL_Event* event) override;
  
  inline void UpdateText(std::string text) { m_DisplayText = text; }
  inline void UpdatePositionX(int x) { m_X = x; }
  inline void UpdatePositionY(int y) { m_Y = y; }
  inline void UpdateWidth(int width) { m_Width = width; }
  inline void UpdateHeight(int height) { m_Height = height; }
  inline int GetPositionX() { return m_X; }
  inline int GetPositionY() { return m_Y; }
  inline int GetWidth() { return m_Width; }
  inline int GetHeight() { return m_Height; }

protected:
  int m_X, m_Y;
  int m_Width, m_Height;
  std::string m_DisplayText;
  TTF_Font* m_Font;
  SDL_Color m_TextColor;
  SDL_Color m_BackgroundColor;
  std::array<int, 4> m_CornerRadius;
  SDL_Surface* m_BackgroundSurface;
  Image m_Image;
  
  bool m_TextCenteredX;
  bool m_TextCenteredY;
  int m_TextBufferX;
  int m_TextBufferY;
};

#endif //!LABEL_H
