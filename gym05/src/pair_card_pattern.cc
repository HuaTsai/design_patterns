#include "pair_card_pattern.hpp"

bool PairCardPatternRecognizer::Match(std::vector<std::shared_ptr<Card>> cards) const {
  return cards.size() == 2 && cards[0]->rank() == cards[1]->rank();
}

std::shared_ptr<CardPattern> PairCardPatternRecognizer::CreateConcreteCardPatternImpl(
    std::vector<std::shared_ptr<Card>> cards) const {
  return std::make_shared<PairCardPattern>(cards, "對子");
}
