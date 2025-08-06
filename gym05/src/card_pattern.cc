#include "card_pattern.hpp"

#include <algorithm>

CardPattern::CardPattern(const std::vector<std::shared_ptr<Card>> &cards, const std::string &name)
    : cards_(cards), name_(name) {
  std::ranges::sort(cards_, [](auto a, auto b) { return *a < *b; });
}

std::strong_ordering CardPattern::operator<=>(const CardPattern &other) const {
  auto max_card = *std::ranges::max_element(cards_, [](auto a, auto b) { return *a < *b; });
  auto other_max_card =
      *std::ranges::max_element(other.cards_, [](auto a, auto b) { return *a < *b; });
  return *max_card <=> *other_max_card;
}

std::string CardPattern::string() const {
  std::string ret;
  ret += name_ + " ";
  for (auto card : cards_) {
    if (card == cards_.back()) {
      ret += card->string();
    } else {
      ret += card->string() + " ";
    }
  }
  return ret;
}

std::ostream &operator<<(std::ostream &os, std::shared_ptr<CardPattern> card) {
  return os << card->string();
}

CardPatternRecognizer::CardPatternRecognizer(std::shared_ptr<CardPatternRecognizer> next)
    : next_(next) {}

std::shared_ptr<CardPattern> CardPatternRecognizer::CreateConcreteCardPattern(
    const std::vector<std::shared_ptr<Card>> &cards) const {
  if (Match(cards)) {
    return CreateConcreteCardPatternImpl(cards);
  } else if (next_) {
    return next_->CreateConcreteCardPattern(cards);
  }
  return nullptr;
}
