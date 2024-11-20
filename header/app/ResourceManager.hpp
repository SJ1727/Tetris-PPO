#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <string>
#include "log.hpp"

class ResourceManager {
public:
  ResourceManager() = default;
  ~ResourceManager();

  bool LoadFont(std::string path, int fontSize, std::string alias);
  TTF_Font* GetFont(std::string alias);

  bool LoadMusic(std::string path, std::string alias);
  Mix_Music* GetMusic(std::string alias);

  bool LoadSoundEffect(std::string path, std::string alias);
  Mix_Chunk* GetSoundEffect(std::string alias);

  bool LoadImage(std::string path, std::string alias);
  SDL_Surface* GetImage(std::string alias);

private:
  std::unordered_map<std::string, TTF_Font*> m_FontMap;
  std::unordered_map<std::string, Mix_Music*> m_MusicMap;
  std::unordered_map<std::string, Mix_Chunk*> m_SoundEffectMap;
  std::unordered_map<std::string, SDL_Surface*> m_ImageMap;
};

#endif // !RESOURCE_MANAGER_H
