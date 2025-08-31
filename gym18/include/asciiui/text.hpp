#pragma once

#include <string>

struct Text {
  Text(int x, int y, const std::wstring &text) : x(x), y(y), text(text) {}
  int x;
  int y;
  std::wstring text;
};