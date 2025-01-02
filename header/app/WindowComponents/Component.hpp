#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SDL3/SDL.h>

#define TRANSPARENT {0, 0, 0, 0}
#define BLACK {0, 0, 0, 255}
#define GRAY {128, 128, 128, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}

class Component {
public:
  virtual void HandleEvents(SDL_Event* event) = 0;
  virtual void Render(SDL_Renderer* renderer) = 0;
  virtual void Update() {}
};

#endif // !COMPONENTS_H

