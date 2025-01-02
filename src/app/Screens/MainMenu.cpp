#include "app/Screens/MainMenu.hpp"

void MainMenuScreen::LoadResources() {
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 32, "Def 32");
  m_ResourceManager.LoadFont("resources/font/Jersey10-Regular.ttf", 70, "Def 70");
  m_ResourceManager.LoadMusic("resources/sound/MainMenu_piano.ogg", "Main Menu Music");
  m_ResourceManager.LoadImage("resources/images/settings_icon.png", "Settings Icon");
  m_ResourceManager.LoadImage("resources/images/question_mark.png", "Question Mark");
  m_ResourceManager.LoadSoundEffect("resources/sound/Click1.wav", "Button Click");
}

void MainMenuScreen::Init(ScreenManager* screenManager) {
  LoadResources();

  TTF_Font* normalFont = m_ResourceManager.GetFont("Def 32");
  TTF_Font* titleFont = m_ResourceManager.GetFont("Def 70");
  SDL_Surface* settingsIcon = m_ResourceManager.GetImage("Settings Icon");
  SDL_Surface* helpIcon = m_ResourceManager.GetImage("Question Mark");
  Mix_Chunk* buttonClick = m_ResourceManager.GetSoundEffect("Button Click");
  m_BackgroundSurface = CreateSingleColorSurface(m_Width, m_Height, BACKGROUND_COLOR);

  /* Defining components settings */
  LabelSettings titleTextSettings;
  SetTitleStyle(&titleTextSettings);
  titleTextSettings.text = "Tetris";
  titleTextSettings.font = titleFont;

  ButtonSettings singlePlayerButtonSettings;
  SetButtonStyle(&singlePlayerButtonSettings, RIGHT_CORNER_RADIUS(20));
  singlePlayerButtonSettings.text = "Single Player";
  singlePlayerButtonSettings.font = normalFont;
  
  ButtonSettings localMultiButtonSettings;
  SetButtonStyle(&localMultiButtonSettings, RIGHT_CORNER_RADIUS(20));
  localMultiButtonSettings.text = "Local Multiplayer";
  localMultiButtonSettings.font = normalFont;
  
  ButtonSettings versusAiButtonSettings;
  SetButtonStyle(&versusAiButtonSettings, RIGHT_CORNER_RADIUS(20));
  versusAiButtonSettings.text = "Player vs AI";
  versusAiButtonSettings.font = normalFont;

  ButtonSettings settingsButtonSettings;
  SetButtonStyle(&settingsButtonSettings, BOTTOM_CORNER_RADIUS(20));
  settingsButtonSettings.imageDefault = { settingsIcon, 40, 40 };
  settingsButtonSettings.onClickSound = buttonClick;

  ButtonSettings helpButtonSettings;
  SetButtonStyle(&helpButtonSettings, BOTTOM_CORNER_RADIUS(20));
  helpButtonSettings.imageDefault = { helpIcon, 40, 40 };
  helpButtonSettings.onClickSound = buttonClick;

  LabelSettings gameInfomationBackgroundSettings;
  SetLabelStyle(&gameInfomationBackgroundSettings, LEFT_CORNER_RADIUS(20));
  
  LabelSettings highScoreLabelSettings;
  highScoreLabelSettings.text = "High Score";
  highScoreLabelSettings.font = normalFont;
  highScoreLabelSettings.textColor = WHITE;
  
  LabelSettings highScoreNumberLabelSettings;
  highScoreNumberLabelSettings.text = "xxx";
  highScoreNumberLabelSettings.font = normalFont;
  highScoreNumberLabelSettings.textColor = WHITE;
  
  LabelSettings mostLinesLabelSettings;
  mostLinesLabelSettings.text = "Most Lines Cleared";
  mostLinesLabelSettings.font = normalFont;
  mostLinesLabelSettings.textColor = WHITE;
  
  LabelSettings mostLinesNumberLabelSettings;
  mostLinesNumberLabelSettings.text = "xxx";
  mostLinesNumberLabelSettings.font = normalFont;
  mostLinesNumberLabelSettings.textColor = WHITE;
  
  LabelSettings timePlayedLabelSettings;
  timePlayedLabelSettings.text = "Hours Played";
  timePlayedLabelSettings.font = normalFont;
  timePlayedLabelSettings.textColor = WHITE;
  
  LabelSettings timePlayedNumberLabelSettings;
  timePlayedNumberLabelSettings.text = "xxx";
  timePlayedNumberLabelSettings.font = normalFont;
  timePlayedNumberLabelSettings.textColor = WHITE;

  /* Create components */
  Label* titleText = new Label(528, 10, 100, 100, titleTextSettings);

  Button* singlePlayerButton = new Button(440, 140, 360, 80, singlePlayerButtonSettings); 
  Button* localMultiButton = new Button(440, 260, 360, 80, localMultiButtonSettings); 
  Button* versusAiButton = new Button(440, 380, 360, 80, versusAiButtonSettings); 
  
  Button* settingsButton = new Button(480, 520, 80, 80, settingsButtonSettings); 
  Button* helpButton = new Button(640, 520, 80, 80, helpButtonSettings); 

  Label* gameInfomationBackground = new Label(0, 50, 280, 500, gameInfomationBackgroundSettings);
  Line* gameInfomationLine1 = new Line(0, 206, 280, 206, BACKGROUND_COLOR);
  Line* gameInfomationLine2 = new Line(0, 374, 280, 374, BACKGROUND_COLOR);
  Label* highScoreLabel = new Label(68, 60, 122, 34, highScoreLabelSettings);
  Label* highScoreNumberLabel = new Label(108, 124, 42, 34, highScoreNumberLabelSettings);
  Label* mostLinesLabel = new Label(34, 216, 204, 34, mostLinesLabelSettings);
  Label* mostLinesNumberLabel = new Label(108, 284, 42, 34, mostLinesNumberLabelSettings);
  Label* timePlayedLabel = new Label(58, 384, 146, 34, timePlayedLabelSettings);
  Label* timePlayedNumberLabel = new Label(108, 446, 42, 34, timePlayedNumberLabelSettings);

  /* Create Animations */
  Animation* singlePlayerButtonAnimation = AnimateButtonStretchLeft(singlePlayerButton, 30, 300);
  Animation* localMultiButtonAnimation = AnimateButtonStretchLeft(localMultiButton, 30, 300);
  Animation* versusAiButtonAnimation = AnimateButtonStretchLeft(versusAiButton, 30, 300);
  Animation* settingButtonAnimation = AnimateButtonStretchUp(settingsButton, 10, 300);
  Animation* helpButtonAnimation = AnimateButtonStretchUp(helpButton, 10, 300);

  /* Adding bindings to components */
  singlePlayerButton->AddHoverAnimation(singlePlayerButtonAnimation);
  localMultiButton->AddHoverAnimation(localMultiButtonAnimation);
  versusAiButton->AddHoverAnimation(versusAiButtonAnimation);
  settingsButton->AddHoverAnimation(settingButtonAnimation);
  helpButton->AddHoverAnimation(helpButtonAnimation);

  singlePlayerButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SINGLE_PLAYER_GAME));
  settingsButton->BindClick(std::bind(&ScreenManager::SetScreen, screenManager, SETTINGS));

  /* Linking the components to the screen */
  Link(titleText);
  Link(singlePlayerButton);
  Link(localMultiButton);
  Link(versusAiButton);
  Link(settingsButton);
  Link(helpButton);
  Link(gameInfomationBackground);
  Link(gameInfomationLine1);
  Link(gameInfomationLine2);
  Link(highScoreLabel);
  Link(highScoreNumberLabel);
  Link(mostLinesLabel);
  Link(mostLinesNumberLabel);
  Link(timePlayedLabel);
  Link(timePlayedNumberLabel);
  
  /* Adding animations */
  AddAnimation(singlePlayerButtonAnimation);
  AddAnimation(localMultiButtonAnimation);
  AddAnimation(versusAiButtonAnimation);
  AddAnimation(settingButtonAnimation);
  AddAnimation(helpButtonAnimation);

  /* Starting Music */
  Mix_Music* music = m_ResourceManager.GetMusic("Main Menu Music");
  Mix_PlayMusic(music, -1);
}

