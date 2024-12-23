#include "app/App.hpp"
#include "log.hpp"
#include "engine/Tetromino.hpp"
#include "engine/TetrisEngine.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  Log::Init();
  //App app(800, 600);
  //app.Run();
  TetrisEngine engine;
  for (int i = 0; i < 100; i++) {
    ENGINE_TRACE(engine.GetBoardAsString());
    engine.SetNextMove(DROP);
    engine.Update();
  }
}
