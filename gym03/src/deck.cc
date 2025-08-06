#include "deck.hpp"

#include <algorithm>
#include <random>

#include "poker_card.hpp"
#include "uno_card.hpp"

std::shared_ptr<Deck> Deck::CreateUNODeck() {
  std::vector<std::shared_ptr<Card>> cards;
  using enum Number;
  using enum Color;
  for (auto number : {kZero, kOne, kTwo, kThree, kFour, kFive, kSix, kSeven, kEight, kNine}) {
    for (auto color : {kRed, kGreen, kBlue, kYellow}) {
      cards.push_back(std::make_shared<UNOCard>(color, number));
    }
  }
  return std::shared_ptr<Deck>(new Deck(cards));
}

std::shared_ptr<Deck> Deck::CreatePokerDeck() {
  std::vector<std::shared_ptr<Card>> cards;
  using enum Rank;
  using enum Suit;
  for (auto rank : {kAce, kTwo, kThree, kFour, kFive, kSix, kSeven, kEight, kNine, kTen, kJack,
                    kQueen, kKing}) {
    for (auto suit : {kClub, kDiamond, kHeart, kSpade}) {
      cards.push_back(std::make_shared<PokerCard>(suit, rank));
    }
  }
  // clang-format on
  return std::shared_ptr<Deck>(new Deck(cards));
}

void Deck::Shuffle() { std::ranges::shuffle(cards_, std::default_random_engine{}); }

std::shared_ptr<Card> Deck::Deal() {
  if (cards_.empty()) {
    throw std::out_of_range("No cards left in the deck");
  }
  auto card = cards_.back();
  cards_.pop_back();
  return card;
}

void Deck::AddCards(const std::vector<std::shared_ptr<Card>> &cards) {
  cards_.insert(cards_.end(), cards.begin(), cards.end());
}

bool Deck::IsEmpty() const { return cards_.empty(); }

Deck::Deck(const std::vector<std::shared_ptr<Card>> &cards) : cards_(cards) {}
