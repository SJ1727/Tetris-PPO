#ifndef ANIMATION_H
#define ANIMATION_H

#include <functional>
#include <algorithm>
#include <cmath>

class Animation {
public:
  Animation(std::function<void(int)> animationFunction, int length);
  ~Animation() = default;

  inline void Start() { m_Playing = true; }
  inline void Stop()  { m_Playing = false; }
  void Forward();
  void Backward();
  void Reset();
  void Step(int deltaTime);

private:
  std::function<void(int)> m_AnimationFunction;
  int m_Length;
  int m_TimeElapsed = 0;
  bool m_Playing = false;
  bool m_Backward = false;
};

float EaseInOut(float normalizedTime);

#endif // !ANIMATION_H
