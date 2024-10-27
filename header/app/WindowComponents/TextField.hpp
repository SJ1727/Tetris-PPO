#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H

#include <string>
#include "app/SdlHelper.hpp"
#include "app/WindowComponents/Component.hpp"

typedef struct {
  std::string initial_text = "";
  TTF_Font* font = nullptr;
  SDL_Color text_color = BLACK;
  SDL_Color background_color = WHITE;
  
  bool text_centered_x = false;
  bool text_centered_y = true;
  int text_buffer_x = 5;
  int text_buffer_y = 5;
  
  int cursor_blink_milliseconds = 500;
} TextFieldSettings;

class TextField : public Component {
public:
  TextField(int x, int y, int width, int height, TextFieldSettings settings);
  void render(SDL_Renderer* renderer) override;
  void handleEvents(SDL_Event* event) override;
  void update() override;
  inline void updateText(std::string text) { m_text = text; }
  inline std::string getText() { return m_text; }

private:
  std::string getDisplayText();

private:
  int m_x, m_y;
  int m_width, m_height;
  
  std::string m_text;
  TTF_Font* m_font;
  SDL_Color m_text_color;
  SDL_Color m_background_color;
  bool m_text_centered_x;
  bool m_text_centered_y;
  int m_text_buffer_x;
  int m_text_buffer_y;

  bool m_show_cursor;
  int m_last_cursor_blink_milliseconds;
  int m_cursor_blink_milliseconds;

  bool m_clicked;
};

#endif // !TEXT_FIELD_H
