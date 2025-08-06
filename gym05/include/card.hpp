#pragma once

#include <compare>
#include <format>
#include <memory>

enum class Suit { kClubs = 0, kDiamonds = 1, kHearts = 2, kSpades = 3 };
enum class Rank {
  kThree = 0,
  kFour = 1,
  kFive = 2,
  kSix = 3,
  kSeven = 4,
  kEight = 5,
  kNine = 6,
  kTen = 7,
  kJack = 8,
  kQueen = 9,
  kKing = 10,
  kAce = 11,
  kTwo = 12
};

class Card {
 public:
  Card() = delete;
  explicit Card(const std::string& card);
  explicit Card(Suit suit, Rank rank);
  std::strong_ordering operator<=>(const Card &other) const;
  std::string string() const;

  Suit suit();
  Rank rank();

 private:
  Suit suit_;
  Rank rank_;
};

template <>
struct std::formatter<std::shared_ptr<Card>> : formatter<string> {
  template <typename FormatContext>
  auto format(std::shared_ptr<Card> card, FormatContext &ctx) const {
    return format_to(ctx.out(), "{}", card->string());
  }
};

std::ostream &operator<<(std::ostream &os, std::shared_ptr<Card> card);
