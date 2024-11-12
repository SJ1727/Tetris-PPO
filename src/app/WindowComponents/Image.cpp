#include "app/WindowComponents/Image.hpp"

void renderImage(SDL_Renderer* renderer, Image image, int x, int y, bool center) {
  SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image.surface);
  SDL_FRect image_rectangle;

  if (!center) {
    image_rectangle = createFRect(x, y, image.width, image.height);
  } else {
    image_rectangle = createFRect(x - image.width / 2, y - image.height / 2, image.width, image.height);
  }
  
  SDL_RenderTexture(renderer, image_texture, nullptr, &image_rectangle);
  SDL_DestroyTexture(image_texture);
}
