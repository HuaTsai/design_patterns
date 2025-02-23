#pragma once

#include "card.hpp"

enum class Color { kBlue, kRed, kYellow, kGreen };

enum class Number {
  kZero,
  kOne,
  kTwo,
  kThree,
  kFour,
  kFive,
  kSix,
  kSeven,
  kEight,
  kNine,
};

class UNOCard : public Card {
 public:
  explicit UNOCard(Color color, Number number) : color_(color), number_(number) {}
  std::string string() const override;
  bool HasSameColorOrNumber(const UNOCard &other) const;

 private:
  Color color_;
  Number number_;
};
