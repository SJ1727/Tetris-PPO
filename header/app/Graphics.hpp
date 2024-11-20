#ifndef SDL_HELPER_H
#define SDL_HELPER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <array>
#include <string>

#include "log.hpp"

SDL_Texture* CreateTextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color textColor);

Uint32 SDLColorToUint(SDL_Color color);

SDL_FRect CreateFRect(int x, int y, int w, int h);

SDL_Surface* CreateRoundedRectangleSurface(int width, int height, std::array<int, 4> radius, SDL_Color color);

SDL_Surface* CreateFilledCircle(int radius, SDL_Color color);

SDL_Surface* CreateSingleColorSurface(int width, int height, SDL_Color color);

void FilledSurfaceCircle(SDL_Surface* surface, int x, int y, int radius, SDL_Color color);

#endif //!SDL_HELPER_H
