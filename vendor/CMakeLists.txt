if (TETRIS_ENGINE_BIND_COMPILE)
  add_subdirectory(pybind11)
else()
  add_subdirectory(SDL)
  add_subdirectory(SDL_ttf)
  add_subdirectory(SDL_mixer)
  add_subdirectory(SDL_image)
  add_library(vendor INTERFACE)

  target_link_libraries(vendor INTERFACE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
  )
endif()
