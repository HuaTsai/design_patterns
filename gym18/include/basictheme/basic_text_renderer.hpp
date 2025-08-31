#pragma once

#include <asciiui/text_renderer.hpp>

class BasicTextRenderer : public TextRenderer {
 public:
  using TextRenderer::TextRenderer;

  void Show(const Text &text) override;
};