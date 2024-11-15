#ifndef ANIMATION_H
#define ANIMATION_H

#include <functional>
#include <algorithm>
#include <cmath>

class Animation {
public:
  Animation(std::function<void(int)> animation_function, int length);
  ~Animation() = default;
  void start() { m_playing = true; }
  void stop() { m_playing = false; }
  void forward();
  void backward();
  void reset();
  void step(int delta_time);

private:
  std::function<void(int)> m_animation_function;
  int m_length;
  int m_time_elapsed = 0;
  bool m_playing = false;
  bool m_backward = false;
};

float easeInOut(float normilized_time);

#endif // !ANIMATION_H
