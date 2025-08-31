#pragma once

#include <asciiui/numbered_list_renderer.hpp>

class PrettyNumberedListRenderer : public NumberedListRenderer {
 public:
  using NumberedListRenderer::NumberedListRenderer;

  void Show(const NumberedList &list) override;
};