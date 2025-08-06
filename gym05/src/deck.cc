#include "deck.hpp"

#include <algorithm>
#include <random>

Deck::Deck() {
  // clang-format off
  for (auto suit : {Suit::kHearts, Suit::kDiamonds, Suit::kClubs, Suit::kSpades}) {
    for (auto rank : {Rank::kThree, Rank::kFour, Rank::kFive, Rank::kSix, Rank::kSeven,
                      Rank::kEight, Rank::kNine, Rank::kTen, Rank::kJack, Rank::kQueen,
                      Rank::kKing, Rank::kAce, Rank::kTwo}) {
      cards_.push_back(std::make_shared<Card>(suit, rank));
    }
  }
  // clang-format on
}

Deck::Deck(const std::vector<std::shared_ptr<Card>>& cards) : cards_(cards) {}

void Deck::Shuffle() {
  auto dre = std::default_random_engine(std::random_device{}());
  std::ranges::shuffle(cards_, dre);
}

std::shared_ptr<Card> Deck::Deal() {
  auto ret = cards_.back();
  cards_.pop_back();
  return ret;
}

bool Deck::IsEmpty() { return cards_.empty(); }
