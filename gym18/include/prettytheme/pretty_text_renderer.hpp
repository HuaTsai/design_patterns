#pragma once

#include <asciiui/text_renderer.hpp>

class PrettyTextRenderer : public TextRenderer {
 public:
  using TextRenderer::TextRenderer;

  void Show(const Text &text) override;
};