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

  std::shared_ptr<AppContext> context = std::make_shared<AppContext>();
  context->playMaster = true;
  context->playMusic = true;
  context->playSoundEffects = true;
  context->masterVolume = APP_MAX_VOLUME; 
  context->musicVolume = APP_MAX_VOLUME;
  context->soundEffectsVolume = APP_MAX_VOLUME;

  m_ScreenManager = new ScreenManager(m_Width, m_Height, context);
}

App::~App() {
  SDL_DestroyWindow(m_Window);
  SDL_DestroyRenderer(m_Renderer);
  delete m_ScreenManager;

  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void App::Run() {
  bool running = true;

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
  }
}

