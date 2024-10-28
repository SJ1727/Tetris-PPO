#include "app/ResourceManager.hpp"

ResourceManager::~ResourceManager() {
  for (auto& pair : m_font_map) {
    TTF_CloseFont(pair.second);
  }

  for (auto& pair : m_music_map) {
    Mix_FreeMusic(pair.second);
  }
  
  for (auto& pair : m_sound_effect_map) {
    Mix_FreeChunk(pair.second);
  }

  for (auto& pair : m_image_map) {
    SDL_DestroySurface(pair.second);
  }
}

bool ResourceManager::loadFont(std::string path, int font_size, std::string alias) {
  // Check if there already exist a loaded font with same alias
  if (m_font_map.find(alias) != m_font_map.end()) {
    APP_WARN("Cannot load two fonts with the same alias of \"{}\"", alias);
    return false;
  }

  TTF_Font* font = TTF_OpenFont(path.c_str(), font_size);
  // Check if the font has been loaded
  if (!font) {
    APP_WARN("Failed to load font from \"{}\"", path);
    return false;
  } 

  m_font_map[alias] = font;
  return true;
}

TTF_Font* ResourceManager::getFont(std::string alias) {
  if (m_font_map.find(alias) != m_font_map.end()) {
    return m_font_map[alias];
  }
  
  APP_WARN("Font with alias \"{}\" has not been loaded", alias);
  // Return nullptr if font with alias does not exist
  return nullptr;
}

bool ResourceManager::loadMusic(std::string path, std::string alias) {
  // Check if there already exist a loaded music object with same alias
  if (m_music_map.find(alias) != m_music_map.end()) {
    APP_WARN("Cannot load two music objects with the same alias of \"{}\"", alias);
    return false;
  }

  Mix_Music* music = Mix_LoadMUS(path.c_str());
  // Check if the music has been loaded
  if (!music) {
    APP_WARN("Failed to load music from \"{}\"", path);
    return false;
  } 

  m_music_map[alias] = music;
  return true;
}
Mix_Music* ResourceManager::getMusic(std::string alias) {
  if (m_music_map.find(alias) != m_music_map.end()) {
    return m_music_map[alias];
  }
  
  APP_WARN("Music with alias \"{}\" has not been loaded", alias);
  // Return nullptr if music object with alias does not exist
  return nullptr;
}

bool ResourceManager::loadSoundEffect(std::string path, std::string alias) {
  // Check if there already exist a loaded sound effect with same alias
  if (m_sound_effect_map.find(alias) != m_sound_effect_map.end()) {
    APP_WARN("Cannot load two sound effects with the same alias of \"{}\"", alias);
    return false;
  }

  Mix_Chunk* sound_effect = Mix_LoadWAV(path.c_str());
  // Check if the sound effect has been loaded
  if (!sound_effect) {
    APP_WARN("Failed to load sound effect from \"{}\"", path);
    return false;
  } 

  m_sound_effect_map[alias] = sound_effect;
  return true;
}

Mix_Chunk* ResourceManager::getSoundEffect(std::string alias) {
  if (m_sound_effect_map.find(alias) != m_sound_effect_map.end()) {
    return m_sound_effect_map[alias];
  }
  
  APP_WARN("Sound effect with alias \"{}\" has not been loaded", alias);
  // Return nullptr if sound effect object with alias does not exist
  return nullptr;
}

bool ResourceManager::loadImage(std::string path, std::string alias) {
  // Check if there already exist a loaded image with same alias
  if (m_image_map.find(alias) != m_image_map.end()) {
    APP_WARN("Cannot load two images with the same alias of \"{}\"", alias);
    return false;
  }

  SDL_Surface* image = IMG_Load(path.c_str());
  // Check if the image has been loaded
  if (!image) {
    APP_WARN("Failed to load image from \"{}\"", path);
    return false;
  } 

  m_image_map[alias] = image;
  return true;
}

SDL_Surface* ResourceManager::getImage(std::string alias) {
  if (m_image_map.find(alias) != m_image_map.end()) {
    return m_image_map[alias];
  }

  APP_WARN("Image with alias \"{}\" has not been loaded", alias);
  // Return nullptr if image with alias does not exist
  return nullptr;
}
