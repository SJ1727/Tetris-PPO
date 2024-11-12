#ifndef IMAGE_H
#define IMAGE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include "app/SdlHelper.hpp"

typedef struct {
  SDL_Surface* surface = nullptr;
  int width = 0;
  int height = 0;
} Image;

void renderImage(SDL_Renderer* renderer, Image image, int x, int y, bool center=false);

#endif // IMAGE_H
