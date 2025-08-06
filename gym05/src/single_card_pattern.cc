#include "single_card_pattern.hpp"

bool SingleCardPatternRecognizer::Match(const std::vector<std::shared_ptr<Card>>& cards) const {
  return cards.size() == 1;
}

std::shared_ptr<CardPattern> SingleCardPatternRecognizer::CreateConcreteCardPatternImpl(
    const std::vector<std::shared_ptr<Card>>& cards) const {
  return std::make_shared<SingleCardPattern>(cards, "單張");
}
