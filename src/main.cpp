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
  Tetromino testPeice(I, ROTATION_0, {0, 0});
  for (int i = 0; i < NUM_TETROMINO_TYPES; i++) {
    for (int j = 0; j < 4; j++) {
      testPeice = {static_cast<TetrominoType>(i), static_cast<Rotation>(j), {0, 4 * j}};
      engine.PlaceTetromino(testPeice);
    }

    ENGINE_TRACE(engine.GetBoardAsString());
    engine.Init();
  }
}
