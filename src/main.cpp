#include "app/App.hpp"
#include "log.hpp"
#include "engine/Tetromino.hpp"
#include "engine/TetrisEngine.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  Log::Init();
  // App app(800, 600);
  // app.Run();
  TetrisEngine engine;
  ENGINE_TRACE(engine.GetBoardAsString());
}
