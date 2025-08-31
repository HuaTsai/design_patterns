#include <asciiui/asciiui.hpp>
#include <asciiui/numbered_list.hpp>
#include <basictheme/basic_numbered_list_renderer.hpp>

void BasicNumberedListRenderer::Show(const NumberedList &list) {
  auto &data = ui()->data();
  for (size_t i = 0; i < list.lines_of_texts.size(); ++i) {
    data[list.y + i][list.x] = static_cast<wchar_t>(L'1' + i);
    data[list.y + i][list.x + 1] = L'.';
    for (size_t j = 0; j < list.lines_of_texts[i].size(); ++j) {
      data[list.y + i][list.x + 3 + j] = list.lines_of_texts[i][j];
    }
  }
}