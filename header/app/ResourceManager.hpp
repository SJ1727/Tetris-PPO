#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <iostream>

class ResourceManager {
public:
  ResourceManager();
  ~ResourceManager();

  bool loadFont(std::string path, int font_size, std::string alias);
  TTF_Font* getFont(std::string alias);

  bool loadMusic(std::string path, std::string alias);
  Mix_Music* getMusic(std::string alias);

  bool loadImage(std::string path, std::string alias);
  SDL_Surface* getImage(std::string alias);

private:
  std::unordered_map<std::string, TTF_Font*> m_font_map;
  std::unordered_map<std::string, Mix_Music*> m_music_map;
  std::unordered_map<std::string, SDL_Surface*> m_image_map;
};

#endif // !RESOURCE_MANAGER_H
