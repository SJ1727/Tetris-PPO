add_subdirectory(SDL)
add_subdirectory(SDL_ttf)
add_subdirectory(SDL_mixer)
add_subdirectory(SDL_image)
add_subdirectory(spdlog)
add_subdirectory(pybind11)
add_library(vendor INTERFACE)

target_link_libraries(vendor INTERFACE
  SDL3::SDL3
  SDL3_ttf::SDL3_ttf
  SDL3_image::SDL3_image
  SDL3_mixer::SDL3_mixer
  spdlog::spdlog
)
