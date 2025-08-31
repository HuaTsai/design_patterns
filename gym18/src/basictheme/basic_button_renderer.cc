#include <asciiui/asciiui.hpp>
#include <asciiui/button.hpp>
#include <basictheme/basic_button_renderer.hpp>

void BasicButtonRenderer::Show(const Button &button) {
  auto &data = ui()->data();
  const int width = 2 * button.padding_h + static_cast<int>(button.text.size()) + 2;
  const int height = 2 * button.padding_v + 3;
  data[button.y][button.x] = L'+';
  data[button.y][button.x + width - 1] = L'+';
  data[button.y + height - 1][button.x] = L'+';
  data[button.y + height - 1][button.x + width - 1] = L'+';
  for (int i = button.y + 1; i < button.y + height - 1; ++i) {
    data[i][button.x] = L'|';
    data[i][button.x + width - 1] = L'|';
  }
  for (int i = button.x + 1; i < button.x + width - 1; ++i) {
    data[button.y][i] = L'-';
    data[button.y + height - 1][i] = L'-';
  }
  for (size_t i = 0; i < button.text.size(); ++i) {
    data[button.y + 1][button.x + button.padding_h + 1 + i] = button.text[i];
  }
}