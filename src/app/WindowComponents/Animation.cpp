#include "app/WindowComponents/Animation.hpp"

Animation::Animation(std::function<void(int)> animationFunction, int length)
  : m_AnimationFunction(animationFunction), m_Length(length) {

}

void Animation::Forward() {
  if (!m_Playing) { Start(); }
  m_Backward = false;
}

void Animation::Backward() {
  if (!m_Playing) { Start(); }
  m_Backward = true;
}

void Animation::Reset() {
  m_TimeElapsed = 0;
  m_Backward = false;
  m_AnimationFunction(0);
}

void Animation::Step(int deltaTime) {
  if (!m_Playing) { return; }

  if (m_Backward) {
    m_TimeElapsed -= deltaTime;
  } else {
    m_TimeElapsed += deltaTime;
  }

  // Clamping time elapsed between 0 and length
  m_TimeElapsed = std::min(m_Length, m_TimeElapsed);
  m_TimeElapsed = std::max(0, m_TimeElapsed);

  m_AnimationFunction(m_TimeElapsed);

  if (m_TimeElapsed == 0 && m_Backward) { Stop(); }
  if (m_TimeElapsed == m_Length && !m_Backward) { Stop(); }
}

float EaseInOut(float normilizedTime) {
  if (normilizedTime < 0.5) {
    return 4 * std::pow(normilizedTime, 3);
  }

  return 1 - std::pow(-2 * normilizedTime + 2, 3) / 2;
}
