#include "app/WindowComponents/Label.hpp"

Label::Label(int x, int y, int width, int height, LabelSettings settings)
  : m_x(x), m_y(y), m_width(width), m_height(height) {
  m_text = settings.text;
  m_font = settings.font;
  m_text_color = settings.text_color;
  m_background_color = settings.background_color;
  m_image_surface = settings.image_surface;

  // Alpha channel for text color must be zero otherwise will just renderer as a colored rectangle
  m_text_color.a = 0;
}

void Label::updateText(std::string text) {
  m_text = text;
}

void Label::render(SDL_Renderer* renderer) {
  int text_x, text_y, text_width, text_height;
  SDL_FRect label_rectangle = createFRect(m_x, m_y, m_width, m_height);
  
  // Renders background with one solid color
  SDL_SetRenderDrawColor(renderer, m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a);
  SDL_RenderFillRect(renderer, &label_rectangle);
  
  // Renders the image AFTER the solid color so it is infront
  if (m_image_surface != nullptr) {  
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, m_image_surface);  
    
    // Renders image as labels background
    SDL_RenderTexture(renderer, image_texture, nullptr, &label_rectangle);
    SDL_DestroyTexture(image_texture);
  }


  if (m_text != " ") {
    SDL_Texture* text_texture = createTextTexture(renderer, m_text, m_font, m_text_color);
    
    // Calculate position of text rectangle so it is centred
    text_x = (m_width - text_texture->w) / 2 + m_x;
    text_y = (m_height - text_texture->h) / 2 + m_y;
      
    // Rendering Text
    SDL_FRect text_rectangle = createFRect(text_x, text_y, text_texture->w, text_texture->h);
    SDL_RenderTexture(renderer, text_texture, nullptr, &text_rectangle);
    SDL_DestroyTexture(text_texture);
  }
  
}

void Label::handleEvents(SDL_Event* event) {

}
