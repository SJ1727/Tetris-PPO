#include "app/Screens/VolumeSettings.hpp"

auto resetVolume = [](std::shared_ptr<AppContext> context) {
    context->masterVolume = DEFAULT_VOLUME;
    context->musicVolume = DEFAULT_VOLUME;
    context->soundEffectsVolume = DEFAULT_VOLUME;
};

void VolumeSettingsScreen::ChangeMuted(bool* volumeMuted) {
  *volumeMuted = !(*volumeMuted);
}

void VolumeSettingsScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Volume";
  titleTextSettings.font = resourceManager->GetFont("Font 70");
  
  ButtonSettings muteButtonSettings;
  SetButtonStyle(&muteButtonSettings, RIGHT_CORNER_RADIUS(20));
  muteButtonSettings.text = "Mute";
  muteButtonSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };

  ButtonSettings resetButtonSettings;
  SetButtonStyle(&resetButtonSettings, LEFT_CORNER_RADIUS(20));
  resetButtonSettings.text = "Reset";
  resetButtonSettings.font = resourceManager->GetFont("Font 32");
  
  SliderSettings<int> masterVolumeSliderSettings;
  SetSliderStyle(&masterVolumeSliderSettings);
	masterVolumeSliderSettings.min = 0;
	masterVolumeSliderSettings.max = APP_MAX_VOLUME;
  
  SliderSettings<int> musicVolumeSliderSettings;
  SetSliderStyle(&musicVolumeSliderSettings);
	musicVolumeSliderSettings.min = 0;
	musicVolumeSliderSettings.max = APP_MAX_VOLUME;
  
  SliderSettings<int> soundEffectsVolumeSliderSettings;
  SetSliderStyle(&soundEffectsVolumeSliderSettings);
	soundEffectsVolumeSliderSettings.min = 0;
	soundEffectsVolumeSliderSettings.max = APP_MAX_VOLUME;

  LabelSettings masterVolumeLabelSettings;
  SetLabelStyle(&masterVolumeLabelSettings, LEFT_CORNER_RADIUS(20));
  masterVolumeLabelSettings.text = "Master Volume";
  masterVolumeLabelSettings.font = resourceManager->GetFont("Font 32");

  LabelSettings musicVolumeLabelSettings;
  SetLabelStyle(&musicVolumeLabelSettings, LEFT_CORNER_RADIUS(20));
  musicVolumeLabelSettings.text = "Music Volume";
  musicVolumeLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings soundEffectsVolumeLabelSettings;
  SetLabelStyle(&soundEffectsVolumeLabelSettings, LEFT_CORNER_RADIUS(20));
  soundEffectsVolumeLabelSettings.text = "Sound FX Volume";
  soundEffectsVolumeLabelSettings.font = resourceManager->GetFont("Font 32");
  
  /* Create components */
  Label* titleText = new Label(528, 10, 100, 100, titleTextSettings);
  
  Button* returnButton = new Button(640, 520, 80, 80, returnButtonSettings); 
  
  Button* resetButton = new Button(0, 520, 220, 50, resetButtonSettings); 
  
  Slider<int>* masterVolumeSlider = new Slider<int>(250, 140, 300, 60, &m_Context->masterVolume, masterVolumeSliderSettings); 
  Slider<int>* musicVolumeSlider = new Slider<int>(250, 270, 300, 60, &m_Context->musicVolume, musicVolumeSliderSettings); 
  Slider<int>* soundEffectsVolumeSlider = new Slider<int>(250, 400, 300, 60, &m_Context->soundEffectsVolume, soundEffectsVolumeSliderSettings); 
  
  Label* masterVolumeLabel = new Label(0, 130, 220, 80, masterVolumeLabelSettings);
  Label* musicVolumeLabel = new Label(0, 260, 220, 80, musicVolumeLabelSettings);
  Label* soundEffectsVolumeLabel = new Label(0, 390, 220, 80, soundEffectsVolumeLabelSettings);

  Button* muteMasterVolumeButton = new Button(580, 130, 220, 80, muteButtonSettings);
  Button* muteMusicVolumeButton = new Button(580, 260, 220, 80, muteButtonSettings);
  Button* muteSoundEffectsVolumeButton = new Button(580, 390, 220, 80, muteButtonSettings);


  returnButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));
  
  resetButton->BindClick(std::bind(resetVolume, m_Context));
  
  muteMasterVolumeButton->BindClick(std::bind(VolumeSettingsScreen::ChangeMuted, &m_Context->playMaster));
  muteMusicVolumeButton->BindClick(std::bind(VolumeSettingsScreen::ChangeMuted, &m_Context->playMusic)); 
  muteSoundEffectsVolumeButton->BindClick(std::bind(VolumeSettingsScreen::ChangeMuted, &m_Context->playSoundEffects));
 
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
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
