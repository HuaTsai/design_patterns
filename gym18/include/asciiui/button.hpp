#pragma once

#include <array>
#include <string>

struct Button {
  Button(int x, int y, int padding_h, int padding_v, const std::wstring &text)
      : x(x), y(y), padding_h(padding_h), padding_v(padding_v), text(text) {}
  int x;
  int y;
  int padding_h;
  int padding_v;
  std::wstring text;
};