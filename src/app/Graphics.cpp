#include "app/Graphics.hpp"

SDL_Texture* CreateTextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color textColor) {
  SDL_Texture* textTexture;
  
  if (font == nullptr) {
    LOG_ERROR("Unable to create text texture since font is null");
    return nullptr;
  }

  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, text.c_str(), text.length(), textColor, textColor);

  if (textSurface) {
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);
  } else {
    textTexture = nullptr;
    LOG_ERROR("Could not create text surface with text " + text);
  }

  return textTexture;
}

Uint32 SDLColorToUint(SDL_Color color) {
  Uint32 colorUint = 0;
  colorUint |= color.r << 24;
  colorUint |= color.g << 16;
  colorUint |= color.b << 8;
  colorUint |= color.a;
  return colorUint;
}

SDL_FRect CreateFRect(int x, int y, int w, int h) {
  return { (float)x, (float)y, (float)w, (float)h };
}

SDL_Surface* CreateSingleColorSurface(int width, int height, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);

  SDL_FillSurfaceRect(surface, NULL, SDLColorToUint(color));

  return surface;
}


SDL_Surface* CreateRoundedRectangleSurface(int width, int height, std::array<int, 4> radius, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);

   if ((radius[0] + radius[1]) > width || (radius[2] + radius[3]) > height) {
    LOG_ERROR("Cannot create rounded rectanlge with width=" + std::to_string(width) +  "height=" + std::to_string(height));
    return surface;
  }

  // Draw the corners
  FilledSurfaceCircle(surface, radius[0], radius[0], radius[0], color);                  // Top left
  FilledSurfaceCircle(surface, width - radius[1], radius[1], radius[1], color);          // Top right
  FilledSurfaceCircle(surface, radius[2], height - radius[2], radius[2], color);         // Bottom Left
  FilledSurfaceCircle(surface, width - radius[3], height - radius[3], radius[3], color); // Bottom right

  // Fill in center
  SDL_Rect topRectangle = { radius[0], 0, width - radius[0] - radius[1], height / 2 };
  SDL_Rect bottomRectangle = { radius[2], height / 2, width - radius[2] - radius[3], height / 2 };
  SDL_Rect leftRectangle = { 0, radius[0], width / 2, height - radius[0] - radius[2] };
  SDL_Rect rightRectangle = { width / 2, radius[1], width / 2, height - radius[1] - radius[3] };
  
  SDL_FillSurfaceRect(surface, &topRectangle, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &bottomRectangle, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &leftRectangle, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &rightRectangle, SDLColorToUint(color));

  return surface;
}

SDL_Surface* CreateFilledCircle(int radius, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(radius, radius, SDL_PIXELFORMAT_RGBA8888);

  FilledSurfaceCircle(surface, radius / 2, radius / 2, radius, color);

  return surface;
}

void FilledSurfaceCircle(SDL_Surface* surface, int x, int y, int radius, SDL_Color color) {
  int dx, dy;

  // O(n^2) probs better way of doing it
  for (int w = 0; w < 2 * radius; w++) {
    for (int h = 0; h < 2 * radius; h++) {
      dx = radius - w;
      dy = radius - h;
      if ((dx * dx + dy * dy) < (radius * radius)) {
        ((Uint32 *)surface->pixels)[x + dx + (y + dy) * surface->w] = SDLColorToUint(color);
      }
    }
  }
}
