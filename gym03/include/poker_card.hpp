#pragma once

#include <compare>

#include "card.hpp"

enum class Suit { kClub = 0, kDiamond = 1, kHeart = 2, kSpade = 3 };

enum class Rank {
  kAce = 14,
  kTwo = 2,
  kThree = 3,
  kFour = 4,
  kFive = 5,
  kSix = 6,
  kSeven = 7,
  kEight = 8,
  kNine = 9,
  kTen = 10,
  kJack = 11,
  kQueen = 12,
  kKing = 13
};

class PokerCard : public Card {
 public:
  explicit PokerCard(Suit suit, Rank rank) : suit_(suit), rank_(rank) {}
  std::strong_ordering operator<=>(const PokerCard &other) const;
  std::string string() const override;

 private:
  Suit suit_;
  Rank rank_;
};
