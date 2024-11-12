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


SDL_Surface* createRoundedRectangleSurface(int width, int height, std::array<int, 4> radius, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);

   if ((radius[0] + radius[1]) > width || (radius[2] + radius[3]) > height) {
    APP_ERROR("Cannot create rounded rectanlge with width={}, height={}", width, height);
    return surface;
  }

  // Draw the corners
  FilledSurfaceCircle(surface, radius[0], radius[0], radius[0], color);                  // Top left
  FilledSurfaceCircle(surface, width - radius[1], radius[1], radius[1], color);          // Top right
  FilledSurfaceCircle(surface, radius[2], height - radius[2], radius[2], color);         // Bottom Left
  FilledSurfaceCircle(surface, width - radius[3], height - radius[3], radius[3], color); // Bottom right

  // Fill in center
  SDL_Rect top_rectangle = { radius[0], 0, width - radius[0] - radius[1], height / 2 };
  SDL_Rect bottom_rectangle = { radius[2], height / 2, width - radius[2] - radius[3], height / 2 };
  SDL_Rect left_rectangle = { 0, radius[0], width / 2, height - radius[0] - radius[2] };
  SDL_Rect right_rectangle = { width / 2, radius[1], width / 2, height - radius[1] - radius[3] };
  
  SDL_FillSurfaceRect(surface, &top_rectangle, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &bottom_rectangle, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &left_rectangle, SDLColorToUint(color));
  SDL_FillSurfaceRect(surface, &right_rectangle, SDLColorToUint(color));

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
