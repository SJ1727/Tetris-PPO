#include "app/Screens/VolumeSettings.hpp"

auto resetVolume = [](std::shared_ptr<AppContext> context) {
    context->masterVolume = DEFAULT_VOLUME;
    context->musicVolume = DEFAULT_VOLUME;
    context->soundEffectsVolume = DEFAULT_VOLUME;
};

void VolumeSettingsScreen::ChangeVolume(int* volume, int newVolume) {
  *volume = newVolume;
}

void VolumeSettingsScreen::ChangeMuted(bool* volumeMuted) {
  *volumeMuted = !(*volumeMuted);
}

void VolumeSettingsScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
  m_ResourceManager.LoadFont("resources/font/ahronbd.ttf", 20, "Default font 25");
  m_ResourceManager.LoadImage("resources/images/return_icon.png", "Return Icon");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
}

void VolumeSettingsScreen::Init(ScreenManager* screenManager) {
  LoadResources();
  
  const SDL_Color BACKGROUND_COLOR = { 22, 22, 22, 255};

  TTF_Font* titleFont = m_ResourceManager.GetFont("Def 70");
  TTF_Font* normalFont = m_ResourceManager.GetFont("Default font 25");
  SDL_Surface* returnIcon = m_ResourceManager.GetImage("Return Icon");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);

  /* Defining components settings */
  SliderSettings baseVolumeSliderSettings;
  baseVolumeSliderSettings.min = 0;
  baseVolumeSliderSettings.max = APP_MAX_VOLUME;
  baseVolumeSliderSettings.trackPaddingX = 20;
  baseVolumeSliderSettings.trackPaddingY = 25;
  baseVolumeSliderSettings.thumbRelativeSize = 8;
  baseVolumeSliderSettings.backgroundColor = { 76, 75, 75, 255 };
  baseVolumeSliderSettings.trackColor = { 217, 217, 217, 255 };
  baseVolumeSliderSettings.thumbColor = BACKGROUND_COLOR;
  baseVolumeSliderSettings.backgroundCornerRadius = { 20, 20, 20, 20 };
  baseVolumeSliderSettings.trackCornerRadius = { 5, 5, 5, 5 };
  baseVolumeSliderSettings.thumbCornerRadius = { 12, 12, 12, 12 };

  LabelSettings baseVolumeLabelSettings;
  baseVolumeLabelSettings.font = normalFont;
  baseVolumeLabelSettings.textColor = WHITE;
  baseVolumeLabelSettings.cornerRadius = { 0, 20, 0, 20 };
  baseVolumeLabelSettings.backgroundColor = { 51, 51, 51, 255 };

  ButtonSettings baseMuteButtonSettings;
  baseMuteButtonSettings.text = "Mute";
  baseMuteButtonSettings.font = normalFont;
  baseMuteButtonSettings.textColor = WHITE;
  baseMuteButtonSettings.cornerRadius = { 20, 0, 20, 0 };
  baseMuteButtonSettings.backgroundDefaultColor = { 76, 75, 75, 255 };
  
  LabelSettings titleTextSettings;
  titleTextSettings.text = "Volume";
  titleTextSettings.font = titleFont;
  titleTextSettings.textColor = WHITE;
  titleTextSettings.backgroundColor = TRANSPARENT;
  
  ButtonSettings returnButtonSettings;
  returnButtonSettings.imageDefault = { returnIcon, 40, 40 };
  returnButtonSettings.backgroundDefaultColor = { 76, 75, 75, 255 };
  returnButtonSettings.cornerRadius = { 20, 20, 0, 0 };

  ButtonSettings resetButtonSettings;
  resetButtonSettings.text = "Reset";
  resetButtonSettings.font = normalFont;
  resetButtonSettings.textColor = WHITE;
  resetButtonSettings.backgroundDefaultColor = { 76, 75, 75, 255 };
  resetButtonSettings.cornerRadius = { 0, 20, 0, 20 };
  
  SliderSettings masterVolumeSliderSettings = baseVolumeSliderSettings;
  masterVolumeSliderSettings.startingValue = m_Context->masterVolume;
  
  SliderSettings musicVolumeSliderSettings = baseVolumeSliderSettings;
  musicVolumeSliderSettings.startingValue = m_Context->musicVolume;
  
  SliderSettings soundEffectsVolumeSliderSettings = baseVolumeSliderSettings;
  soundEffectsVolumeSliderSettings.startingValue = m_Context->soundEffectsVolume;

  LabelSettings masterVolumeLabelSettings = baseVolumeLabelSettings;
  masterVolumeLabelSettings.text = "Master Volume";

  LabelSettings musicVolumeLabelSettings = baseVolumeLabelSettings;
  musicVolumeLabelSettings.text = "Music Volume";
  
  LabelSettings soundEffectsVolumeLabelSettings = baseVolumeLabelSettings;
  soundEffectsVolumeLabelSettings.text = "Sound FX Volume";
  
  /* Create components */
  Label* titleText = new Label(528, 10, 100, 100, titleTextSettings);
  
  Button* returnButton = new Button(640, 520, 80, 80, returnButtonSettings); 
  
  Button* resetButton = new Button(0, 520, 220, 50, resetButtonSettings); 
  
  Slider* masterVolumeSlider = new Slider(250, 140, 300, 60, masterVolumeSliderSettings); 
  Slider* musicVolumeSlider = new Slider(250, 270, 300, 60, musicVolumeSliderSettings); 
  Slider* soundEffectsVolumeSlider = new Slider(250, 400, 300, 60, soundEffectsVolumeSliderSettings); 
  
  Label* masterVolumeLabel = new Label(0, 130, 220, 80, masterVolumeLabelSettings);
  Label* musicVolumeLabel = new Label(0, 260, 220, 80, musicVolumeLabelSettings);
  Label* soundEffectsVolumeLabel = new Label(0, 390, 220, 80, soundEffectsVolumeLabelSettings);

  Button* muteMasterVolumeButton = new Button(580, 130, 220, 80, baseMuteButtonSettings);
  Button* muteMusicVolumeButton = new Button(580, 260, 220, 80, baseMuteButtonSettings);
  Button* muteSoundEffectsVolumeButton = new Button(580, 390, 220, 80, baseMuteButtonSettings);


  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));
  
  resetButton->BindClick(std::bind(resetVolume, m_Context));
  
  muteMasterVolumeButton->BindClick(std::bind(VolumeSettingsScreen::ChangeMuted, &m_Context->playMaster));
  muteMusicVolumeButton->BindClick(std::bind(VolumeSettingsScreen::ChangeMuted, &m_Context->playMusic)); 
  muteSoundEffectsVolumeButton->BindClick(std::bind(VolumeSettingsScreen::ChangeMuted, &m_Context->playSoundEffects));
 
  masterVolumeSlider->Bind(std::bind(VolumeSettingsScreen::ChangeVolume, &m_Context->masterVolume, std::placeholders::_1));
  musicVolumeSlider->Bind(std::bind(VolumeSettingsScreen::ChangeVolume, &m_Context->musicVolume, std::placeholders::_1));
  soundEffectsVolumeSlider->Bind(std::bind(VolumeSettingsScreen::ChangeVolume, &m_Context->soundEffectsVolume, std::placeholders::_1));
  
  /* Create Animations */
  Animation* returnButtonAnimation = AnimateButtonStretchUp(returnButton, 10, 300);
  Animation* resetButtonAnimation = AnimateButtonStretchRight(resetButton, 15, 300);
  Animation* muteMasterVolumeButtonAnimation = AnimateButtonStretchLeft(muteMasterVolumeButton, 15, 300);
  Animation* muteMusicVolumeButtonAnimation = AnimateButtonStretchLeft(muteMusicVolumeButton, 15, 300);
  Animation* muteSoundEffectsVolumeButtonAnimation = AnimateButtonStretchLeft(muteSoundEffectsVolumeButton, 15, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  resetButton->AddHoverAnimation(resetButtonAnimation);
  muteMasterVolumeButton->AddHoverAnimation(muteMasterVolumeButtonAnimation);
  muteMusicVolumeButton->AddHoverAnimation(muteMusicVolumeButtonAnimation);
  muteSoundEffectsVolumeButton->AddHoverAnimation(muteSoundEffectsVolumeButtonAnimation);
  
  /* Linking the components to the screen */
  Link(titleText);
  Link(returnButton);
  Link(resetButton);
  Link(masterVolumeSlider);
  Link(musicVolumeSlider);
  Link(soundEffectsVolumeSlider);
  Link(masterVolumeLabel);
  Link(musicVolumeLabel);
  Link(soundEffectsVolumeLabel);
  Link(muteMasterVolumeButton);
  Link(muteMusicVolumeButton);
  Link(muteSoundEffectsVolumeButton);
  
  /* Adding animations */
  AddAnimation(returnButtonAnimation);
  AddAnimation(resetButtonAnimation);
  AddAnimation(muteMasterVolumeButtonAnimation);
  AddAnimation(muteMusicVolumeButtonAnimation);
  AddAnimation(muteSoundEffectsVolumeButtonAnimation);

  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}
