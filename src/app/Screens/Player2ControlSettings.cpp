#include "app/Screens/Player2ControlSettings.hpp"

void Player2ControlSettingsScreen::Init(std::shared_ptr<ScreenManager> screenManager, std::shared_ptr<ResourceManager> resourceManager) {
  SetBackgroundColor(BACKGROUND_COLOR);

  m_CurrentCommandToSwitch = NONE;
  
  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Player 2 Controls";
  titleTextSettings.font = resourceManager->GetFont("Font 70");
  
  ButtonSettings returnButtonSettings;
  SetButtonStyle(&returnButtonSettings, BOTTOM_CORNER_RADIUS(20));
  returnButtonSettings.imageDefault = { resourceManager->GetImage("Return Icon"), 40, 40 };

  LabelSettings holdLabelSettings;
  SetLabelStyle(&holdLabelSettings, LEFT_CORNER_RADIUS(20));
  holdLabelSettings.text = "Hold";
  holdLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings holdKeybindButtonSettings;
  SetButtonStyle(&holdKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  holdKeybindButtonSettings.font = resourceManager->GetFont("Font 32");


  LabelSettings downLabelSettings;
  SetLabelStyle(&downLabelSettings, LEFT_CORNER_RADIUS(20));
  downLabelSettings.text = "Move Down";
  downLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings downKeybindButtonSettings;
  SetButtonStyle(&downKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  downKeybindButtonSettings.font = resourceManager->GetFont("Font 32");


  LabelSettings rightLabelSettings;
  SetLabelStyle(&rightLabelSettings, LEFT_CORNER_RADIUS(20));
  rightLabelSettings.text = "Move Right";
  rightLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings rightKeybindButtonSettings;
  SetButtonStyle(&rightKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  rightKeybindButtonSettings.font = resourceManager->GetFont("Font 32");


  LabelSettings leftLabelSettings;
  SetLabelStyle(&leftLabelSettings, LEFT_CORNER_RADIUS(20));
  leftLabelSettings.text = "Move Left";
  leftLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings leftKeybindButtonSettings;
  SetButtonStyle(&leftKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  leftKeybindButtonSettings.font = resourceManager->GetFont("Font 32");
  

  LabelSettings dropLabelSettings;
  SetLabelStyle(&dropLabelSettings, LEFT_CORNER_RADIUS(20));
  dropLabelSettings.text = "Drop";
  dropLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings dropKeybindButtonSettings;
  SetButtonStyle(&dropKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  dropKeybindButtonSettings.font = resourceManager->GetFont("Font 32");


  LabelSettings rotCWLabelSettings;
  SetLabelStyle(&rotCWLabelSettings, LEFT_CORNER_RADIUS(20));
  rotCWLabelSettings.text = "Rot. Clockwise";
  rotCWLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings rotCWKeybindButtonSettings;
  SetButtonStyle(&rotCWKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  rotCWKeybindButtonSettings.font = resourceManager->GetFont("Font 32");


  LabelSettings rotACWLabelSettings;
  SetLabelStyle(&rotACWLabelSettings, LEFT_CORNER_RADIUS(20));
  rotACWLabelSettings.text = "Rot. Anit Clockwise";
  rotACWLabelSettings.font = resourceManager->GetFont("Font 32");
  
  ButtonSettings rotACWKeybindButtonSettings;
  SetButtonStyle(&rotACWKeybindButtonSettings, ALL_CORNER_RADIUS(20));
  rotACWKeybindButtonSettings.font = resourceManager->GetFont("Font 32");
  

  /* Create components */
  CREATE_LABEL(titleText, 528, 10, 100, 100, titleTextSettings);
  
  CREATE_BUTTON(returnButton, 640, 520, 80, 80, returnButtonSettings); 

  CREATE_LABEL(holdLabel, 0, 100, 220, 60, holdLabelSettings);
  CREATE_LABEL(downLabel, 0, 170, 220, 60, downLabelSettings);
  CREATE_LABEL(rightLabel, 0, 240, 220, 60, rightLabelSettings);
  CREATE_LABEL(leftLabel, 0, 310, 220, 60, leftLabelSettings);
  CREATE_LABEL(dropLabel, 0, 380, 220, 60, dropLabelSettings);
  CREATE_LABEL(rotCWLabel, 0, 450, 220, 60, rotCWLabelSettings);
  CREATE_LABEL(rotACWLabel, 0, 520, 220, 60, rotACWLabelSettings);
  
  CREATE_BUTTON(holdBindButton, 250, 100, 220, 60, holdKeybindButtonSettings);
  CREATE_BUTTON(downBindButton, 250, 170, 220, 60, downKeybindButtonSettings);
  CREATE_BUTTON(rightBindButton, 250, 240, 220, 60, rightKeybindButtonSettings);
  CREATE_BUTTON(leftBindButton, 250, 310, 220, 60, leftKeybindButtonSettings);
  CREATE_BUTTON(dropBindButton, 250, 380, 220, 60, dropKeybindButtonSettings);
  CREATE_BUTTON(rotCWBindButton, 250, 450, 220, 60, rotCWKeybindButtonSettings);
  CREATE_BUTTON(rotACWBindButton, 250, 520, 220, 60, rotACWKeybindButtonSettings);
  
  
  returnButton->BindClick(CHANGE_SCREEN(screenManager, CONTROL_SETTINGS));

  holdBindButton  ->BindClick(SET_VALUE(m_CurrentCommandToSwitch, HOLD         , KeyCommand));
  downBindButton  ->BindClick(SET_VALUE(m_CurrentCommandToSwitch, DOWN         , KeyCommand));
  rightBindButton ->BindClick(SET_VALUE(m_CurrentCommandToSwitch, RIGHT        , KeyCommand));
  leftBindButton  ->BindClick(SET_VALUE(m_CurrentCommandToSwitch, LEFT         , KeyCommand));
  dropBindButton  ->BindClick(SET_VALUE(m_CurrentCommandToSwitch, DROP         , KeyCommand));
  rotCWBindButton ->BindClick(SET_VALUE(m_CurrentCommandToSwitch, ROTATE_RIGHT , KeyCommand));
  rotACWBindButton->BindClick(SET_VALUE(m_CurrentCommandToSwitch, ROTATE_RIGHT , KeyCommand));

  m_HoldBindButton = holdBindButton;
  m_DownBindButton = downBindButton;
  m_RightBindButton = rightBindButton;
  m_LeftBindButton = leftBindButton;
  m_DropBindButton = dropBindButton;
  m_RotCWBindButton = rotCWBindButton;
  m_RotACWBindButton = rotACWBindButton;
  
  /* Starting Music */
  Mix_PlayMusic(resourceManager->GetMusic("Menu Music"), -1);
}

void Player2ControlSettingsScreen::HandleEvents(SDL_Event* event) {
  Screen::HandleEvents(event);
  LOG_TRACE("--- Current switch ---" + std::to_string((int) m_CurrentCommandToSwitch));

  if (m_CurrentCommandToSwitch != NONE && event->type == SDL_EVENT_KEY_DOWN) {
    LOG_TRACE("Current switch " + std::to_string((int) m_CurrentCommandToSwitch));

    switch (m_CurrentCommandToSwitch) {
      case HOLD:
        m_Context->player2KeyBindings.hold = event->key.key;
        break;
      case DOWN:
        m_Context->player2KeyBindings.down = event->key.key;
        break;
      case RIGHT:
        m_Context->player2KeyBindings.right = event->key.key;
        break;
      case LEFT:
        m_Context->player2KeyBindings.left = event->key.key;
        break;
      case DROP:
        m_Context->player2KeyBindings.drop = event->key.key;
        break;
      case ROTATE_RIGHT:
        m_Context->player2KeyBindings.rotateRight = event->key.key;
        break;
      case ROTATE_LEFT:
        m_Context->player2KeyBindings.rotateLeft = event->key.key;
        break;
      default:
        break;
    }

    m_CurrentCommandToSwitch = NONE;
  }
}

void Player2ControlSettingsScreen::Update() {
  m_HoldBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.hold));
  m_DownBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.down));
  m_RightBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.right));
  m_LeftBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.left));
  m_DropBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.drop));
  m_RotCWBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.rotateRight));
  m_RotACWBindButton->UpdateText(KeyCodeToString(m_Context->player2KeyBindings.rotateLeft));
  
  Screen::Update();
}
