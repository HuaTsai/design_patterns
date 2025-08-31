#include <asciiui/asciiui.hpp>
#include <asciiui/text.hpp>
#include <prettytheme/pretty_text_renderer.hpp>

void PrettyTextRenderer::Show(const Text &text) {
  auto &data = ui()->data();
  for (size_t i = 0; i < text.text.size(); ++i) {
    data[text.y][text.x + i] = std::toupper(text.text[i]);
  }
}