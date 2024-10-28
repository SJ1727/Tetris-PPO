#include "app/App.hpp"

const int FRAME_DELAY = 1000 / 60;

App::App(int width, int height)
  : m_width(width), m_height(height) {
  APP_TRACE("--- Starting Application ---");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    APP_ERROR("Init Fail: Could not initlise SDL");
  }
  
  if (!TTF_Init()) {
    APP_ERROR("Init Fail: Could not initlise SDL TTF");
  }

  if (!IMG_Init(IMG_INIT_PNG)) {
    APP_ERROR("Init Fail: Could not initlise SDL image");
  }

  SDL_AudioSpec spec;
  spec.freq = MIX_DEFAULT_FREQUENCY;
  spec.format = MIX_DEFAULT_FORMAT;
  spec.channels = 1;

  if (!Mix_OpenAudio(0, &spec)) {
    APP_ERROR("Init Fail: Could not initlise SDL mixer");
  }

  m_window = SDL_CreateWindow("Tetris", m_width, m_height, 0);
  m_renderer = SDL_CreateRenderer(m_window, NULL);

  // Allows for text input to window
  SDL_StartTextInput(m_window);
  
  // Allows for use of the alpha color channel
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

  std::shared_ptr<AppContext> context = std::make_shared<AppContext>();
  context->play_music = true;
  context->music_volume = MIX_MAX_VOLUME;

  m_screen_manager = new ScreenManager(m_width, m_height, context);
}

App::~App() {
  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
  delete m_screen_manager;

  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void App::run() {
  bool running = true;
  int frame_start;
  int frame_length;

  m_screen_manager->setScreen(MAIN_MENU);

  // Main loop
  while (running) {
    // Checking for events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }

      m_screen_manager->handleEvents(&event);
    }

    m_screen_manager->render(m_renderer);
    m_screen_manager->update();

    // Rendering
    SDL_RenderPresent(m_renderer);
  }
}

