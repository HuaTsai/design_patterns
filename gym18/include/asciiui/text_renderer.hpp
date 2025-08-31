#pragma once

#include <asciiui/text.hpp>
#include <memory>

class ASCIIUI;

class TextRenderer {
 public:
  explicit TextRenderer(const std::shared_ptr<ASCIIUI> &ui) : ui_(ui) {}
  virtual ~TextRenderer() = default;
  TextRenderer(const TextRenderer &) = delete;
  TextRenderer &operator=(const TextRenderer &) = delete;
  TextRenderer(TextRenderer &&) = delete;
  TextRenderer &operator=(TextRenderer &&) = delete;

  virtual void Show(const Text &text) = 0;

  std::shared_ptr<ASCIIUI> ui() const { return ui_; }

 private:
  std::shared_ptr<ASCIIUI> ui_;
};