#include "app/App.hpp"
#include "log.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  Log::init();
  App app(800, 600);
  app.run();
}
