#pragma once

#include <asciiui/numbered_list.hpp>
#include <memory>

class ASCIIUI;

class NumberedListRenderer {
 public:
  explicit NumberedListRenderer(const std::shared_ptr<ASCIIUI> &ui) : ui_(ui) {}
  virtual ~NumberedListRenderer() = default;
  NumberedListRenderer(const NumberedListRenderer &) = delete;
  NumberedListRenderer &operator=(const NumberedListRenderer &) = delete;
  NumberedListRenderer(NumberedListRenderer &&) = delete;
  NumberedListRenderer &operator=(NumberedListRenderer &&) = delete;

  virtual void Show(const NumberedList &list) = 0;

  std::shared_ptr<ASCIIUI> ui() const { return ui_; }

 private:
  std::shared_ptr<ASCIIUI> ui_;
};