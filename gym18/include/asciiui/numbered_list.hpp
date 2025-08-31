#pragma once

#include <string>
#include <vector>

struct NumberedList {
  NumberedList(int x, int y, const std::vector<std::wstring> &lines_of_texts)
      : x(x), y(y), lines_of_texts(lines_of_texts) {}
  int x;
  int y;
  std::vector<std::wstring> lines_of_texts;
};