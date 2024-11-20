#include "app/WindowComponents/Label.hpp"

Label::Label(int x, int y, int width, int height, LabelSettings settings)
  : m_X(x), m_Y(y), m_Width(width), m_Height(height) {
  m_DisplayText = settings.text;
  m_Font = settings.font;
  m_TextColor = settings.textColor;
  m_CornerRadius = settings.cornerRadius;
  m_BackgroundColor = settings.backgroundColor;
  m_Image = settings.image;
  
  m_TextCenteredX = settings.textCenteredX;
  m_TextCenteredY = settings.textCenteredY;
  m_TextBufferX = settings.textBufferX;
  m_TextBufferY = settings.textBufferY;

  m_BackgroundSurface = CreateRoundedRectangleSurface(m_Width, m_Height, m_CornerRadius, m_BackgroundColor);

  // Alpha channel for text color must be zero otherwise will just renderer as a colored rectangle
  m_TextColor.a = 0;
}

void Label::Render(SDL_Renderer* renderer) {
  int textX, textY, textWidth, textHeight;
  SDL_FRect labelRectangle = CreateFRect(m_X, m_Y, m_Width, m_Height);
  
  // Renders background
  SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, m_BackgroundSurface); 
  SDL_RenderTexture(renderer, backgroundTexture, nullptr, &labelRectangle);
  
  SDL_DestroyTexture(backgroundTexture);
  
  // Renders the image AFTER the solid color so it is infront
  if (m_Image.surface != nullptr) {  
    RenderImage(renderer, m_Image, m_X + m_Width / 2, m_Y + m_Height / 2, true); 
  }

  if (m_DisplayText != " ") {
    SDL_Texture* textTexture = CreateTextTexture(renderer, m_DisplayText, m_Font, m_TextColor);
    
    // Calculate position of text rectangle
    textX = m_X + (m_TextCenteredX ? (m_Width - textTexture->w) / 2 : m_TextBufferX);
    textY = m_Y + (m_TextCenteredY ? (m_Height - textTexture->h) / 2 : m_TextBufferY);
    textWidth = m_Width - 2 * (textX - m_X);
    textHeight = m_Height - 2 * (textY - m_Y);

    int textRectangleWidth = std::min(textTexture->w, textWidth);
    int clippingX = std::max(textTexture->w, textWidth) - textWidth;
      
    // Rendering Text
    SDL_FRect textRectangle = CreateFRect(textX, textY, textRectangleWidth, textTexture->h);
    SDL_FRect clippingRectangle = CreateFRect(clippingX, 0, textRectangleWidth, textTexture->h);

    SDL_RenderTexture(renderer, textTexture, &clippingRectangle, &textRectangle);
    SDL_DestroyTexture(textTexture);
  }
  
}

void Label::HandleEvents(SDL_Event* event) {

}
