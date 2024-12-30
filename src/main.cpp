#include "app/App.hpp"
#include "log.hpp"
#include "engine/Tetromino.hpp"
#include "engine/TetrisEngine.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  Logger::Init("tetris.log");
  Logger::ClearLog();
  App app(800, 600);
  app.Run();
}
