#include "app/SdlHelper.hpp"

SDL_Texture* createTextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color textColor) {
  SDL_Texture* text_texture;
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

SDL_FRect createFRect(int x, int y, int w, int h) {
  return { (float)x, (float)y, (float)w, (float)h };
}

SDL_Surface* createSingleColorSurface(int width, int height, SDL_Color color) {
  SDL_Surface* surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA8888);

  // Convert the color into an uint
  Uint32 color_uint = 0;
  color_uint |= color.r << 24;
  color_uint |= color.g << 16;
  color_uint |= color.b << 8;
  color_uint |= color.a;

  SDL_FillSurfaceRect(surface, NULL, color_uint);

  return surface;
}