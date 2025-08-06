#include "deck.hpp"

#include <algorithm>
#include <random>

Deck::Deck() {
  for (int i = 1; i <= kNumOfRanks; ++i) {
    using enum Suit;
    for (const Suit suit : {Club, Diamond, Heart, Spade}) {
      cards_.push_back(std::make_shared<Card>(i, suit));
    }
  }
}

void Deck::Shuffle() {
  auto rng = std::default_random_engine{};
  std::ranges::shuffle(cards_, rng);
}

std::shared_ptr<Card> Deck::Deal() {
  auto ret = cards_.back();
  cards_.pop_back();
  return ret;
}
