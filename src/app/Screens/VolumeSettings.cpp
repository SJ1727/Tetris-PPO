#include "app/Screens/VolumeSettings.hpp"

void VolumeSettingsScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/ahronbd.ttf", 25, "Default font 25");
  m_ResourceManager.LoadImage("resources/images/return_icon.png", "Return Icon");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}


void VolumeSettingsScreen::Init(ScreenManager* screenManager) {
  LoadResources();
  
  const SDL_Color BACKGROUND_COLOR = {19, 19, 19, 255};
  TTF_Font* normalFont = m_ResourceManager.GetFont("Default font 25");
  SDL_Surface* returnIcon = m_ResourceManager.GetImage("Return Icon");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);
  
  /* Defining components settings */
  ButtonSettings returnButtonSettings;
  returnButtonSettings.imageDefault = { returnIcon, 40, 40 };
  
  SliderSettings musicVolumeSliderSettings;
  musicVolumeSliderSettings.min = 0;
  musicVolumeSliderSettings.max = MIX_MAX_VOLUME;
  musicVolumeSliderSettings.startingValue = m_Context->musicVolume;
  musicVolumeSliderSettings.trackPaddingX = 10;
  musicVolumeSliderSettings.trackPaddingY = 20;
  musicVolumeSliderSettings.thumbRelativeSize = 3;

  LabelSettings musicVolumeLabelSettings;
  musicVolumeLabelSettings.text = "MUSIC VOLUME";
  musicVolumeLabelSettings.font = normalFont;
  musicVolumeLabelSettings.textColor = WHITE;
  musicVolumeLabelSettings.textCenteredX = false;
  
  SliderSettings soundEffectsVolumeSliderSettings;
  soundEffectsVolumeSliderSettings.min = 0;
  soundEffectsVolumeSliderSettings.max = MIX_MAX_VOLUME;
  soundEffectsVolumeSliderSettings.startingValue = m_Context->soundEffectsVolume;
  soundEffectsVolumeSliderSettings.trackPaddingX = 10;
  soundEffectsVolumeSliderSettings.trackPaddingY = 20;
  soundEffectsVolumeSliderSettings.thumbRelativeSize = 3;

  LabelSettings soundEffectsVolumeLabelSettings;
  soundEffectsVolumeLabelSettings.text = "SOUND FX VOLUME";
  soundEffectsVolumeLabelSettings.font = normalFont;
  soundEffectsVolumeLabelSettings.textColor = WHITE;
  soundEffectsVolumeLabelSettings.textCenteredX = false;
  
  /* Create components */
  Button* returnButton = new Button(20, 530, 50, 50, returnButtonSettings);
  Slider* musicVolumeSlider = new Slider(260, 18, 200, 50, musicVolumeSliderSettings); 
  Label* musicVolumeLabel = new Label(20, 20, 200, 50, musicVolumeLabelSettings);
  Slider* soundEffectsVolumeSlider = new Slider(260, 68, 200, 50, soundEffectsVolumeSliderSettings); 
  Label* soundEffectsVolumeLabel = new Label(20, 70, 250, 50, soundEffectsVolumeLabelSettings);

  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));

  musicVolumeSlider->Bind(std::bind(
    [](std::shared_ptr<AppContext> context, float volume) { 
      context->musicVolume = (int)volume;
    }, m_Context, std::placeholders::_1));
  
  soundEffectsVolumeSlider->Bind(std::bind(
    [](std::shared_ptr<AppContext> context, float volume) { 
      context->soundEffectsVolume = (int)volume;
    }, m_Context, std::placeholders::_1));
  
  /* Linking the components to the screen */
  Link(returnButton);
  Link(musicVolumeSlider);
  Link(musicVolumeLabel);
  Link(soundEffectsVolumeSlider);
  Link(soundEffectsVolumeLabel);
  
  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
