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
    if (i % 1 == 0) {
      ENGINE_TRACE("{}", i);
      ENGINE_TRACE(engine.GetBoardAsString());
    }

    if (i % 5 == 0) {
      engine.SetNextMove(ROTATE_RIGHT);
    } else {
      engine.SetNextMove(DOWN);
    }
    engine.Update();
  }
}
