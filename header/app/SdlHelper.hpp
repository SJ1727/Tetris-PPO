#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "log.hpp"

SDL_Texture* createTextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color text_color);
Uint32 SDLColorToUint(SDL_Color color);
SDL_FRect createFRect(int x, int y, int w, int h);
SDL_Surface* createRoundedRectangleSurface(int width, int height, int radius, SDL_Color color);
SDL_Surface* createSingleColorSurface(int width, int height, SDL_Color color);
void FilledSurfaceCircle(SDL_Surface* surface, int x, int y, int radius, SDL_Color color);

#endif //!SDL_HELPER_H
