#include "app/Screens/AISettings.hpp"

void AISettingsScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  /* Defining components settings */
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };
  
  LabelSettings modelPathLabelSettings;
  modelPathLabelSettings.text = "MODEL PATH";
  modelPathLabelSettings.font = resourceManager->GetFont("Font 25");
  modelPathLabelSettings.textColor = WHITE;
  modelPathLabelSettings.textCenteredX = false;
  
  TextFieldSettings modelPathFieldSettings;
  modelPathFieldSettings.initialText = "example/path/model.onnx";
  modelPathFieldSettings.font = resourceManager->GetFont("Text Field Font 15");
  
  /* Create components */
  CREATE_BUTTON(returnButton, 20, 530, 50, 50, returnButtonSettings);
  CREATE_LABEL(modelPathLabel, 20, 20, 200, 50, modelPathLabelSettings);
  CREATE_TEXT_FIELD(modelPathField, 190, 30, 400, 25, modelPathFieldSettings);
  
  returnButton->BindClick(CHANGE_SCREEN(screenManager, SETTINGS));
  
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}
