#pragma once

#include <format>
#include <iostream>

enum class Suit {
  Club = 0,
  Diamond = 1,
  Heart = 2,
  Spade = 3,
};

class Card {
 public:
  explicit Card(int rank, Suit suit);
  auto operator<=>(const Card &other) const;
  std::string string() const;

 private:
  int rank_;
  Suit suit_;
};

template <>
struct std::formatter<Card> : formatter<string> {
  template <typename FormatContext>
  auto format(const Card &card, FormatContext &ctx) const {
    return format_to(ctx.out(), "{}", card.string());
  }
};

std::ostream &operator<<(std::ostream &os, const Card &card);
