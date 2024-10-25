file(GLOB ENGINE_SOURCES "engine/*.cpp")
file(GLOB_RECURSE APP_SOURCES "app/*.cpp")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

set(SOURCES
  main.cpp
  ${ENGINE_SOURCES}
  ${APP_SOURCES}
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE vendor)
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../header
)
