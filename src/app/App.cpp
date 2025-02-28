#include "app/App.hpp"

App::App(int width, int height)
  : m_Width(width), m_Height(height) {
  LOG_TRACE("--- Starting Application ---");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    LOG_ERROR("Init Fail: Could not initlise SDL");
  }
  
  if (!TTF_Init()) {
    LOG_ERROR("Init Fail: Could not initlise SDL TTF");
  }

  if (!IMG_Init(IMG_INIT_PNG)) {
    LOG_ERROR("Init Fail: Could not initlise SDL image");
  }

  SDL_AudioSpec spec;
  spec.freq = MIX_DEFAULT_FREQUENCY;
  spec.format = MIX_DEFAULT_FORMAT;
  spec.channels = 1;

  if (!Mix_OpenAudio(0, &spec)) {
    LOG_ERROR("Init Fail: Could not initlise SDL mixer");
  }

  m_Window = SDL_CreateWindow("Tetris", m_Width, m_Height, 0);
  m_Renderer = SDL_CreateRenderer(m_Window, NULL);

  // Allows for text input to window
  SDL_StartTextInput(m_Window);
  
  // Allows for use of the alpha color channel
  SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

  m_Context = std::make_shared<AppContext>();
  InitContext();

  m_ResourceManager = std::make_shared<ResourceManager>();
  m_ScreenManager = std::make_shared<ScreenManager>(m_Width, m_Height, m_Context, m_ResourceManager);

  LoadResources();
}

App::~App() {
  SDL_DestroyWindow(m_Window);
  SDL_DestroyRenderer(m_Renderer);

  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void App::Run() {
  bool running = true;
  
  uint64_t lastTime = SDL_GetPerformanceCounter();
  uint64_t currentTime = 0;
  int frames = 0;
  float fps = 0.0f;

  m_ScreenManager->SetScreen(MAIN_MENU);

  // Main loop
  while (running) {
    // Checking for events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }

      m_ScreenManager->HandleEvents(&event);
    }

    m_ScreenManager->Render(m_Renderer);
    m_ScreenManager->Update();

    // Rendering
    SDL_RenderPresent(m_Renderer);

    // Calculating and logging FPS
    currentTime = SDL_GetPerformanceCounter();
    frames++;

    if ((currentTime - lastTime) >= SDL_GetPerformanceFrequency()) {
      fps = frames * (float) SDL_GetPerformanceFrequency() / (currentTime - lastTime);
      lastTime = currentTime;
      frames = 0;
      LOG_INFO("FPS " + std::to_string(fps));
    }
  }
}

void App::InitContext() {
  /* Sound Settings */
  m_Context->playMaster         = true;
  m_Context->playMusic          = true;
  m_Context->playSoundEffects   = true;
  m_Context->masterVolume       = APP_MAX_VOLUME; 
  m_Context->musicVolume        = APP_MAX_VOLUME;
  m_Context->soundEffectsVolume = APP_MAX_VOLUME;

  /* KeyBindings */
  m_Context->player1KeyBindings.hold        = SDLK_RSHIFT;
  m_Context->player1KeyBindings.down        = SDLK_DOWN;
  m_Context->player1KeyBindings.right       = SDLK_RIGHT;
  m_Context->player1KeyBindings.left        = SDLK_LEFT;
  m_Context->player1KeyBindings.drop        = SDLK_SPACE;
  m_Context->player1KeyBindings.rotateRight = SDLK_UP;
  m_Context->player1KeyBindings.rotateLeft  = SDLK_RETURN;
  
  m_Context->player2KeyBindings.hold        = SDLK_C;
  m_Context->player2KeyBindings.down        = SDLK_S;
  m_Context->player2KeyBindings.right       = SDLK_D;
  m_Context->player2KeyBindings.left        = SDLK_A;
  m_Context->player2KeyBindings.drop        = SDLK_Q;
  m_Context->player2KeyBindings.rotateRight = SDLK_W;
  m_Context->player2KeyBindings.rotateLeft  = SDLK_Z;
}

void App::LoadResources() {
  m_ResourceManager->LoadFont("resources/font/Jersey10-Regular.ttf", 25, "Font 25");
  m_ResourceManager->LoadFont("resources/font/Jersey10-Regular.ttf", 32, "Font 32");
  m_ResourceManager->LoadFont("resources/font/Jersey10-Regular.ttf", 70, "Font 70");
  m_ResourceManager->LoadFont("resources/font/JetBrainsMonoNerdFont-Medium.ttf", 15, "Text Field Font 15");
  
  m_ResourceManager->LoadImage("resources/images/return_icon.png", "Return Icon");
  m_ResourceManager->LoadImage("resources/images/settings_icon.png", "Settings Icon");
  m_ResourceManager->LoadImage("resources/images/question_mark.png", "Question Mark Icon");
  
  m_ResourceManager->LoadSoundEffect("resources/sound/Click1.wav", "Button Click");
  
  m_ResourceManager->LoadMusic("resources/sound/MainMenu_piano.ogg", "Menu Music");
  m_ResourceManager->LoadMusic("resources/sound/Korobeiniki_piano.ogg", "Game Music");
}
