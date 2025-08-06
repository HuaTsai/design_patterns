#include "full_house_card_pattern.hpp"

#include <unordered_map>

bool FullHouseCardPatternRecognizer::Match(const std::vector<std::shared_ptr<Card>>& cards) const {
  if (cards.size() != 5) return false;

  std::unordered_map<Rank, int> ranks;
  for (auto card : cards) {
    // prevent four of a kind
    if (++ranks[card->rank()] > 3) return false;
  }

  return ranks.size() == 2;
}

std::shared_ptr<CardPattern> FullHouseCardPatternRecognizer::CreateConcreteCardPatternImpl(
    const std::vector<std::shared_ptr<Card>>& cards) const {
  return std::make_shared<FullHouseCardPattern>(cards, "葫蘆");
}
