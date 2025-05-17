#pragma once

#include <compare>
#include <vector>

#include "card.hpp"

class CardPattern {
 public:
  explicit CardPattern(std::vector<std::shared_ptr<Card>> cards, std::string name);
  virtual ~CardPattern() = default;
  std::strong_ordering operator<=>(const CardPattern &other) const;
  std::string string() const;

 private:
  std::vector<std::shared_ptr<Card>> cards_;
  std::string name_;
};

template <>
struct std::formatter<std::shared_ptr<CardPattern>> : formatter<string> {
  template <typename FormatContext>
  auto format(std::shared_ptr<CardPattern> card_pattern, FormatContext &ctx) const {
    return format_to(ctx.out(), "{}", card_pattern->string());
  }
};

std::ostream &operator<<(std::ostream &os, std::shared_ptr<CardPattern> card);

class CardPatternRecognizer {
 public:
  CardPatternRecognizer(std::shared_ptr<CardPatternRecognizer> next = nullptr);
  virtual bool Match(std::vector<std::shared_ptr<Card>> cards) const = 0;
  virtual std::shared_ptr<CardPattern> CreateConcreteCardPatternImpl(
      std::vector<std::shared_ptr<Card>> cards) const = 0;
  std::shared_ptr<CardPattern> CreateConcreteCardPattern(
      std::vector<std::shared_ptr<Card>> cards) const;

 private:
  std::shared_ptr<CardPatternRecognizer> next_;
};
