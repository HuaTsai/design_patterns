#pragma once

#include <asciiui/button.hpp>
#include <memory>

class ASCIIUI;

class ButtonRenderer {
 public:
  explicit ButtonRenderer(const std::shared_ptr<ASCIIUI> &ui) : ui_(ui) {}
  virtual ~ButtonRenderer() = default;
  ButtonRenderer(const ButtonRenderer &) = delete;
  ButtonRenderer &operator=(const ButtonRenderer &) = delete;
  ButtonRenderer(ButtonRenderer &&) = delete;
  ButtonRenderer &operator=(ButtonRenderer &&) = delete;

  virtual void Show(const Button &button) = 0;

  std::shared_ptr<ASCIIUI> ui() const { return ui_; }

 private:
  std::shared_ptr<ASCIIUI> ui_;
};