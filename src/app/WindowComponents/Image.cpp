#include "app/WindowComponents/Image.hpp"

void RenderImage(SDL_Renderer* renderer, Image image, int x, int y, bool center) {
  SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, image.surface);
  SDL_FRect imageRectangle;

  if (!center) {
    imageRectangle = CreateFRect(x, y, image.width, image.height);
  } else {
    imageRectangle = CreateFRect(x - image.width / 2, y - image.height / 2, image.width, image.height);
  }
  
  SDL_RenderTexture(renderer, imageTexture, nullptr, &imageRectangle);
  SDL_DestroyTexture(imageTexture);
}
