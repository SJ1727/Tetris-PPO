file(GLOB ENGINE_SOURCES "engine/*.cpp")
file(GLOB_RECURSE APP_SOURCES "app/*.cpp")

option(TETRIS_ENGINE_BIND_COMPILE "Compile the tetris engine binding using pybind11" OFF)

set(SOURCES
  main.cpp
  log.cpp
  ${ENGINE_SOURCES}
  ${APP_SOURCES}
)

if(TETRIS_ENGINE_BIND_COMPILE)
  add_library(tetrisEngine STATIC ${ENGINE_SOURCES})
  set_target_properties(tetrisEngine PROPERTIES POSITION_INDEPENDENT_CODE ON)
  target_include_directories(tetrisEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../header
  )
  
  pybind11_add_module(tetris_engine binder.cpp)
  target_link_libraries(tetris_engine PRIVATE tetrisEngine)
else()

  add_executable(${PROJECT_NAME} ${SOURCES})
  target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
  target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../header
  )
endif()
