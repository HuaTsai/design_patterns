#pragma once

#include <memory>

class NumberedListRenderer;
class ButtonRenderer;
class TextRenderer;
class ASCIIUI;

class ThemeFactory {
 public:
  explicit ThemeFactory(const std::shared_ptr<ASCIIUI> &ui) : ui_(ui) {}
  virtual ~ThemeFactory() = default;
  ThemeFactory(const ThemeFactory &) = delete;
  ThemeFactory &operator=(const ThemeFactory &) = delete;
  ThemeFactory(ThemeFactory &&) = delete;
  ThemeFactory &operator=(ThemeFactory &&) = delete;

  virtual std::shared_ptr<NumberedListRenderer> CreateNumberedListRenderer() = 0;
  virtual std::shared_ptr<ButtonRenderer> CreateButtonRenderer() = 0;
  virtual std::shared_ptr<TextRenderer> CreateTextRenderer() = 0;

  std::shared_ptr<ASCIIUI> ui() const { return ui_; }

 private:
  std::shared_ptr<ASCIIUI> ui_;
};