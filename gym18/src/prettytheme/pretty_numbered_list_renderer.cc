#include <asciiui/asciiui.hpp>
#include <asciiui/numbered_list.hpp>
#include <prettytheme/pretty_numbered_list_renderer.hpp>

namespace {
const std::vector<std::wstring> roman_numbers = {L"I",  L"II",  L"III",  L"IV", L"V",
                                                 L"VI", L"VII", L"VIII", L"IX", L"X"};
}

void PrettyNumberedListRenderer::Show(const NumberedList &list) {
  auto &data = ui()->data();
  for (size_t i = 0; i < list.lines_of_texts.size(); ++i) {
    int x = list.x;
    for (size_t j = 0; j < roman_numbers[i].size(); ++j, ++x) {
      data[list.y + i][x] = roman_numbers[i][j];
    }
    data[list.y + i][x] = '.';
    x += 2;
    for (size_t j = 0; j < list.lines_of_texts[i].size(); ++j) {
      data[list.y + i][x + j] = list.lines_of_texts[i][j];
    }
  }
}