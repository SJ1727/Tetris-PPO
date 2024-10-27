#ifndef COMPONENTS_H
#define COMPONENTS_H

#define TRANSPARENT {0, 0, 0, 0}
#define BLACK {0, 0, 0, 255}
#define GRAY {128, 128, 128, 255}
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}
#define GREEN {0, 255, 0, 255}
#define BLUE {0, 0, 255, 255}

class Component {
public:
  virtual void handleEvents(SDL_Event* event) = 0;
  virtual void render(SDL_Renderer* renderer) = 0;
  virtual void update() {}
};

#endif // !COMPONENTS_H

