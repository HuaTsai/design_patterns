#include <asciiui/asciiui.hpp>
#include <asciiui/text.hpp>
#include <basictheme/basic_text_renderer.hpp>

void BasicTextRenderer::Show(const Text &text) {
  auto &data = ui()->data();
  for (size_t i = 0; i < text.text.size(); ++i) {
    data[text.y][text.x + i] = text.text[i];
  }
}