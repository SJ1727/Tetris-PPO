#include "app/ResourceManager.hpp"

ResourceManager::~ResourceManager() {
  for (auto& pair : m_FontMap) {
    TTF_CloseFont(pair.second);
  }

  for (auto& pair : m_MusicMap) {
    Mix_FreeMusic(pair.second);
  }
  
  for (auto& pair : m_SoundEffectMap) {
    Mix_FreeChunk(pair.second);
  }

  for (auto& pair : m_ImageMap) {
    SDL_DestroySurface(pair.second);
  }
}

bool ResourceManager::LoadFont(std::string path, int fontSize, std::string alias) {
  // Check if there already exist a loaded font with same alias
  if (m_FontMap.find(alias) != m_FontMap.end()) {
    LOG_WARN("Cannot load two fonts with the same alias of \"" + alias + "\"");
    return false;
  }

  TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
  // Check if the font has been loaded
  if (!font) {
    LOG_WARN("Failed to load font from \"" + path + "\"");
    return false;
  } 

  m_FontMap[alias] = font;
  return true;
}

TTF_Font* ResourceManager::GetFont(std::string alias) {
  if (m_FontMap.find(alias) != m_FontMap.end()) {
    return m_FontMap[alias];
  }
  
  LOG_WARN("Font with alias \"" + alias + "\" has not been loaded");
  // Return nullptr if font with alias does not exist
  return nullptr;
}

bool ResourceManager::LoadMusic(std::string path, std::string alias) {
  // Check if there already exist a loaded music object with same alias
  if (m_MusicMap.find(alias) != m_MusicMap.end()) {
    LOG_WARN("Cannot load two music objects with the same alias of \"" + alias + "\"");
    return false;
  }

  Mix_Music* music = Mix_LoadMUS(path.c_str());
  // Check if the music has been loaded
  if (!music) {
    LOG_WARN("Failed to load music from \"" + path + "\"");
    return false;
  } 

  m_MusicMap[alias] = music;
  return true;
}
Mix_Music* ResourceManager::GetMusic(std::string alias) {
  if (m_MusicMap.find(alias) != m_MusicMap.end()) {
    return m_MusicMap[alias];
  }
  
  LOG_WARN("Music with alias \"" + alias + "\" has not been loaded");
  // Return nullptr if music object with alias does not exist
  return nullptr;
}

bool ResourceManager::LoadSoundEffect(std::string path, std::string alias) {
  // Check if there already exist a loaded sound effect with same alias
  if (m_SoundEffectMap.find(alias) != m_SoundEffectMap.end()) {
    LOG_WARN("Cannot load two sound effects with the same alias of \"" + alias + "\"");
    return false;
  }

  Mix_Chunk* soundEffect = Mix_LoadWAV(path.c_str());
  // Check if the sound effect has been loaded
  if (!soundEffect) {
    LOG_WARN("Failed to load sound effect from \"" + path + "\"");
    return false;
  } 

  m_SoundEffectMap[alias] = soundEffect;
  return true;
}

Mix_Chunk* ResourceManager::GetSoundEffect(std::string alias) {
  if (m_SoundEffectMap.find(alias) != m_SoundEffectMap.end()) {
    return m_SoundEffectMap[alias];
  }
  
  LOG_WARN("Sound effect with alias \"" + alias + "\" has not been loaded");
  // Return nullptr if sound effect object with alias does not exist
  return nullptr;
}

bool ResourceManager::LoadImage(std::string path, std::string alias) {
  // Check if there already exist a loaded image with same alias
  if (m_ImageMap.find(alias) != m_ImageMap.end()) {
    LOG_WARN("Cannot load two images with the same alias of \"" + alias + "\"");
    return false;
  }

  SDL_Surface* image = IMG_Load(path.c_str());
  // Check if the image has been loaded
  if (!image) {
    LOG_WARN("Failed to load image from \"" + path + "\"");
    return false;
  } 

  m_ImageMap[alias] = image;
  return true;
}

SDL_Surface* ResourceManager::GetImage(std::string alias) {
  if (m_ImageMap.find(alias) != m_ImageMap.end()) {
    return m_ImageMap[alias];
  }

  LOG_WARN("Image with alias \"" + alias + "\" has not been loaded");
  // Return nullptr if image with alias does not exist
  return nullptr;
}
