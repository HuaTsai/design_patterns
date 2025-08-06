#include "straight_card_pattern.hpp"

#include <algorithm>

bool StraightCardPatternRecognizer::Match(const std::vector<std::shared_ptr<Card>>& cards) const {
  if (cards.size() != 5) return false;

  std::vector<int> ranks;
  for (auto card : cards) {
    ranks.push_back(static_cast<int>(card->rank()));
  }
  std::ranges::sort(ranks);

  // Complicated, hard coding is easier
  if (ranks == std::vector<int>({0, 1, 2, 3, 4}) || ranks == std::vector<int>({1, 2, 3, 4, 5}) ||
      ranks == std::vector<int>({2, 3, 4, 5, 6}) || ranks == std::vector<int>({3, 4, 5, 6, 7}) ||
      ranks == std::vector<int>({4, 5, 6, 7, 8}) || ranks == std::vector<int>({5, 6, 7, 8, 9}) ||
      ranks == std::vector<int>({6, 7, 8, 9, 10}) || ranks == std::vector<int>({7, 8, 9, 10, 11}) ||
      ranks == std::vector<int>({8, 9, 10, 11, 12}) ||
      ranks == std::vector<int>({0, 9, 10, 11, 12}) ||
      ranks == std::vector<int>({0, 1, 10, 11, 12}) ||
      ranks == std::vector<int>({0, 1, 2, 11, 12}) || ranks == std::vector<int>({0, 1, 2, 3, 12})) {
    return true;
  }

  return false;
}

std::shared_ptr<CardPattern> StraightCardPatternRecognizer::CreateConcreteCardPatternImpl(
    const std::vector<std::shared_ptr<Card>>& cards) const {
  return std::make_shared<StraightCardPattern>(cards, "順子");
}
