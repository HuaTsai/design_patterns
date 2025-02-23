#pragma once

#include <format>
#include <memory>
#include <ostream>

class Card {
 public:
  virtual ~Card() = default;
  virtual std::string string() const = 0;
};

template <>
struct std::formatter<std::shared_ptr<Card>> : formatter<string> {
  template <typename FormatContext>
  auto format(std::shared_ptr<Card> card, FormatContext &ctx) const {
    return format_to(ctx.out(), "{}", card->string());
  }
};

std::ostream &operator<<(std::ostream &os, std::shared_ptr<Card> card);
