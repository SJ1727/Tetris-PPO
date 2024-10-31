#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <string>
#include "app/SdlHelper.hpp"
#include "app/WindowComponents/Label.hpp"

typedef struct {
  std::string initial_text = "";
  TTF_Font* font = nullptr;
  SDL_Color text_color = BLACK;
  SDL_Color background_color = WHITE;
  int corner_radius = 0;
  
  bool text_centered_x = false;
  bool text_centered_y = true;
  int text_buffer_x = 5;
  int text_buffer_y = 5;
  
  int cursor_blink_milliseconds = 500;
} TextFieldSettings;

class TextField : public Label {
public:
  TextField(int x, int y, int width, int height, TextFieldSettings settings);
  void handleEvents(SDL_Event* event) override;
  void update() override;
  inline void updateText(std::string text) { m_text = text; }
  inline std::string getText() { return m_text; }

private:
  std::string getDisplayText();

private:
  std::string m_text;
  
  bool m_show_cursor;
  int m_last_cursor_blink_milliseconds;
  int m_cursor_blink_milliseconds;

  bool m_clicked;
};

#endif // !TEXT_FIELD_H
