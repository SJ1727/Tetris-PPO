#include "app/WindowComponents/Label.hpp"

Label::Label(int x, int y, int width, int height, LabelSettings settings)
  : m_x(x), m_y(y), m_width(width), m_height(height) {
  m_display_text = settings.text;
  m_font = settings.font;
  m_text_color = settings.text_color;
  m_corner_radius = settings.corner_radius;
  m_background_color = settings.background_color;
  m_image = settings.image;
  
  m_text_centered_x = settings.text_centered_x;
  m_text_centered_y = settings.text_centered_y;
  m_text_buffer_x = settings.text_buffer_x;
  m_text_buffer_y = settings.text_buffer_y;

  m_background_surface = createRoundedRectangleSurface(m_width, m_height, m_corner_radius, m_background_color);

  // Alpha channel for text color must be zero otherwise will just renderer as a colored rectangle
  m_text_color.a = 0;
}

void Label::render(SDL_Renderer* renderer) {
  int text_x, text_y, text_width, text_height;
  SDL_FRect label_rectangle = createFRect(m_x, m_y, m_width, m_height);
  
  // Renders background
  SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, m_background_surface); 
  SDL_RenderTexture(renderer, background_texture, nullptr, &label_rectangle);
  
  SDL_DestroyTexture(background_texture);
  
  // Renders the image AFTER the solid color so it is infront
  if (m_image.surface != nullptr) {  
    renderImage(renderer, m_image, m_x + m_width / 2, m_y + m_height / 2, true); 
  }

  if (m_display_text != " ") {
    SDL_Texture* text_texture = createTextTexture(renderer, m_display_text, m_font, m_text_color);
    
    // Calculate position of text rectangle
    text_x = m_x + (m_text_centered_x ? (m_width - text_texture->w) / 2 : m_text_buffer_x);
    text_y = m_y + (m_text_centered_y ? (m_height - text_texture->h) / 2 : m_text_buffer_y);
    text_width = m_width - 2 * (text_x - m_x);
    text_height = m_height - 2 * (text_y - m_y);

    int text_rectangle_width = std::min(text_texture->w, text_width);
    int clipping_x = std::max(text_texture->w, text_width) - text_width;
      
    // Rendering Text
    SDL_FRect text_rectangle = createFRect(text_x, text_y, text_rectangle_width, text_texture->h);
    SDL_FRect clipping_rectangle = createFRect(clipping_x, 0, text_rectangle_width, text_texture->h);

    SDL_RenderTexture(renderer, text_texture, &clipping_rectangle, &text_rectangle);
    SDL_DestroyTexture(text_texture);
  }
  
}

void Label::handleEvents(SDL_Event* event) {

}
