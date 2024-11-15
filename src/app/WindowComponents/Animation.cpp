#include "app/WindowComponents/Animation.hpp"

Animation::Animation(std::function<void(int)> animation_function, int length)
  : m_animation_function(animation_function), m_length(length) {

}

void Animation::forward() {
  if (!m_playing) { start(); }
  m_backward = false;
}

void Animation::backward() {
  if (!m_playing) { start(); }
  m_backward = true;
}

void Animation::reset() {
  m_time_elapsed = 0;
  m_backward = false;
  m_animation_function(0);
}

void Animation::step(int delta_time) {
  if (!m_playing) { return; }

  if (m_backward) {
    m_time_elapsed -= delta_time;
  } else {
    m_time_elapsed += delta_time;
  }

  // Clamping time elapsed between 0 and length
  m_time_elapsed = std::min(m_length, m_time_elapsed);
  m_time_elapsed = std::max(0, m_time_elapsed);

  m_animation_function(m_time_elapsed);

  if (m_time_elapsed == 0 && m_backward) { stop(); }
  if (m_time_elapsed == m_length && !m_backward) { stop(); }
}

float easeInOut(float normilized_time) {
  if (normilized_time < 0.5) {
    return 4 * std::pow(normilized_time, 3);
  }

  return 1 - std::pow(-2 * normilized_time + 2, 3) / 2;
}
