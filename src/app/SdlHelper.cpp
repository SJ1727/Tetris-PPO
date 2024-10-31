#include "app/SdlHelper.hpp"

SDL_Texture* createTextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color textColor) {
  SDL_Texture* text_texture;
  
  if (font == nullptr) {
    APP_ERROR("Unable to create text texture since font is null");
    return nullptr;
  }

  SDL_Surface* text_surface = TTF_RenderText_Shaded(font, text.c_str(), text.length(), textColor, textColor);

  if (text_surface) {
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_DestroySurface(text_surface);
  } else {
    text_texture = nullptr;
    APP_ERROR("Could not create text surface with text {}", text);
  }

  return text_texture;
}

Uint32 SDLColorToUint(SDL_Color color) {
  Uint32 color_uint = 0;
  color_uint |= color.r << 24;
  color_uint |= color.g << 16;
  color_uint |= color.b << 8;
  color_uint |= color.a;
  return color_uint;
}

SDL_FRect createFRect(int x, int y, int w, int h) {
  return { (float)x, (float)y, (float)w, (float)h };
}

SDL_Surface* createSingleColorSurface(int width, int height, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);

  SDL_FillSurfaceRect(surface, NULL, SDLColorToUint(color));

  return surface;
}


SDL_Surface* createRoundedRectangleSurface(int width, int height, int radius, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);

  if ((2 * radius) > width || (2 * radius) > height) {
    APP_ERROR("Cannot create rounded rectanlge with width={}, height={} with radius={}", width, height, radius);
    return surface;
  }

  // Draw the corners
  FilledSurfaceCircle(surface, radius, radius, radius, color);
  FilledSurfaceCircle(surface, width - radius, radius, radius, color);
  FilledSurfaceCircle(surface, radius, height - radius, radius, color);
  FilledSurfaceCircle(surface, width - radius, height - radius, radius, color);

  // Fill in center
  SDL_Rect middle_rectangle_1 = { radius, 0, width - 2 * radius, height };
  SDL_Rect middle_rectangle_2 = { 0, radius, width, height - 2 * radius };
  SDL_FillSurfaceRect(surface, &middle_rectangle_1, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &middle_rectangle_2, SDLColorToUint(color));

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
