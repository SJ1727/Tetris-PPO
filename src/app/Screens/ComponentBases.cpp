#include "app/Screens/ComponentBases.hpp"

void SetButtonStyle(ButtonSettings* settings, std::array<int, 4> cornerRadius) {
  settings->backgroundDefaultColor = BUTTON_DEFAULT_COLOR;
  settings->backgroundClickedColor = BUTTON_CLICKED_COLOR;
  settings->textColor = WHITE;
  settings->cornerRadius = cornerRadius;
}



void SetLabelStyle(LabelSettings* settings, std::array<int, 4> cornerRadius) {
  settings->backgroundColor = LABEL_COLOR;
  settings->textColor = WHITE;
  settings->cornerRadius = cornerRadius;
}



void SetTitleStyle(LabelSettings* settings) {
  settings->backgroundColor = TRANSPARENT;
  settings->textColor = WHITE;
}



template <typename T>
void SetSliderStyle(SliderSettings<T>* settings) {
	settings->trackPaddingX = 20;
	settings->trackPaddingY = 25;
	settings->thumbRelativeSize = 8;
	settings->backgroundColor = LABEL_COLOR;
	settings->trackColor = BUTTON_DEFAULT_COLOR;
	settings->thumbColor = BACKGROUND_COLOR;
	settings->backgroundCornerRadius = ALL_CORNER_RADIUS(20);
	settings->trackCornerRadius = ALL_CORNER_RADIUS(5);
	settings->thumbCornerRadius = ALL_CORNER_RADIUS(12);
}

template void SetSliderStyle<int>(SliderSettings<int>* settings);
template void SetSliderStyle<float>(SliderSettings<float>* settings);
