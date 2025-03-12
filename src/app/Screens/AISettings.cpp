#include "app/Screens/AISettings.hpp"

void AISettingsScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "AI Player";
  titleTextSettings.font = resourceManager->GetFont("Font 70");
  
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };
  
  LabelSettings modelPathLabelSettings;
  SetLabelStyle(&modelPathLabelSettings, LEFT_CORNER_RADIUS(20));
  modelPathLabelSettings.text = "Model Path";
  modelPathLabelSettings.font = resourceManager->GetFont("Font 32");
  
  TextFieldSettings modelPathFieldSettings;
  modelPathFieldSettings.cornerRadius = ALL_CORNER_RADIUS(20);
  modelPathFieldSettings.initialText = m_Context->aiModelPath;
  modelPathFieldSettings.font = resourceManager->GetFont("Text Field Font 20");
  
  LabelSettings tempertureLabelSettings;
  SetLabelStyle(&tempertureLabelSettings, LEFT_CORNER_RADIUS(20));
  tempertureLabelSettings.text = "Temperture";
  tempertureLabelSettings.font = resourceManager->GetFont("Font 32");
  
  LabelSettings tempertureValueLabelSettings;
  SetLabelStyle(&tempertureValueLabelSettings, RIGHT_CORNER_RADIUS(20));
  tempertureValueLabelSettings.text = "0.0";
  tempertureValueLabelSettings.font = resourceManager->GetFont("Font 32");
  
  SliderSettings<float> tempertureSliderSettings;
  SetSliderStyle(&tempertureSliderSettings);
	tempertureSliderSettings.min = 0.001;
	tempertureSliderSettings.max = 10.0;
  
  /* Create components */
  CREATE_LABEL(titleText, 528, 10, 100, 100, titleTextSettings);
  
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings); 
  
  CREATE_LABEL(modelPathLabel, 0, 160, 200, 60, modelPathLabelSettings);
  CREATE_TEXT_FIELD(modelPathField, 220, 160, 540, 60, modelPathFieldSettings);
  
  CREATE_LABEL(tempertureLabel, 0, 280, 200, 60, tempertureLabelSettings);
  CREATE_LABEL(tempertureValueLabel, 620, 280, 180, 60, tempertureValueLabelSettings);
  CREATE_SLIDER(tempertureSlider, float, 220, 280, 380, 60, &m_Context->aiTemperture, tempertureSliderSettings); 

  m_ModelPathField = modelPathField;
  m_tempertureValueLabel = tempertureValueLabel;
  
  /* Adding bindings to components */
  returnButton->BindClick(CHANGE_SCREEN(screenManager, SETTINGS));
  
  /* Create Animations */
  CREATE_ANIMATION(returnButtonAnimation, AnimateButtonStretchUp, returnButton, 10, 300);
  
  /* Adding bindings to components */
  returnButton->AddHoverAnimation(returnButtonAnimation);
  
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}

void AISettingsScreen::Update() {
  m_Context->aiModelPath = m_ModelPathField->GetText();
  
  m_tempertureValueLabel->UpdateText(std::to_string(m_Context->aiTemperture));

  Screen::Update();
}

