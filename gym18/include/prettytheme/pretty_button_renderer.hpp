#pragma once

#include <asciiui/button_renderer.hpp>

class PrettyButtonRenderer : public ButtonRenderer {
 public:
  using ButtonRenderer::ButtonRenderer;

  void Show(const Button &button) override;
};