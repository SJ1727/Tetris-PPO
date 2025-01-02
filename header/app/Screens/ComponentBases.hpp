#ifndef COMPONENT_BASES_H
#define COMPONENT_BASES_H

#define LEFT_CORNER_RADIUS(radius)   { 0, radius, 0, radius }
#define RIGHT_CORNER_RADIUS(radius)  { radius, 0, radius, 0 }
#define BOTTOM_CORNER_RADIUS(radius) { radius, radius, 0, 0 }
#define TOP_CORNER_RADIUS(radius)    { 0, 0, radius, radius }
#define ALL_CORNER_RADIUS(radius)    { radius, radius, radius, radius }
#define NO_CORNER_RADIUS             { 0, 0, 0, 0 }

#define BACKGROUND_COLOR     { 22, 22, 22, 255 }
#define BUTTON_DEFAULT_COLOR { 76, 75, 75, 255 }
#define BUTTON_CLICKED_COLOR { 46, 45, 45, 255 }
#define LABEL_COLOR          { 51, 51, 51, 255 }

#include <array>
#include "app/WindowComponents/WindowComponents.hpp"

void SetButtonStyle(ButtonSettings* settings, std::array<int, 4> cornerRadius);
void SetLabelStyle(LabelSettings* settings, std::array<int, 4> cornerRadius);
void SetTitleStyle(LabelSettings* settings);
void SetSliderStyle(SliderSettings* settings);

#endif // !COMPONENT_BASES_H
