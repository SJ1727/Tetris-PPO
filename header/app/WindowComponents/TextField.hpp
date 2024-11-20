#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <string>
#include <array>
#include "app/Graphics.hpp"
#include "app/WindowComponents/Label.hpp"

typedef struct {
  std::string initialText = "";
  TTF_Font* font = nullptr;
  SDL_Color textColor = BLACK;
  SDL_Color backgroundColor = WHITE;
  std::array<int, 4> cornerRadius = {0, 0, 0, 0};
  
  bool textCenteredX = false;
  bool textCenteredY = true;
  int textBufferX = 5;
  int textBufferY = 5;
  
  int cursorBlinkMilliseconds = 500;
} TextFieldSettings;

class TextField : public Label {
public:
  TextField(int x, int y, int width, int height, TextFieldSettings settings);
  void HandleEvents(SDL_Event* event) override;
  void Update() override;
  inline void UpdateText(std::string text) { m_Text = text; }
  inline std::string GetText() { return m_Text; }

private:
  std::string GetDisplayText();

private:
  std::string m_Text;
  
  bool m_ShowCursor;
  int m_LastCursorBlinkMilliseconds;
  int m_CursorBlinkMilliseconds;

  bool m_Clicked;
};

#endif // !TEXT_FIELD_H
