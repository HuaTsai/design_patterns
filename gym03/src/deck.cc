#include "deck.hpp"

#include <algorithm>
#include <random>

#include "poker_card.hpp"
#include "uno_card.hpp"

std::shared_ptr<Deck> Deck::CreateUNODeck() {
  std::vector<std::shared_ptr<Card>> cards;
  // clang-format off
  for (auto number : {Number::kZero, Number::kOne, Number::kTwo, Number::kThree,
                      Number::kFour, Number::kFive, Number::kSix,
                      Number::kSeven, Number::kEight, Number::kNine}) {
    for (auto color : {Color::kRed, Color::kGreen, Color::kBlue, Color::kYellow}) {
      cards.push_back(std::make_shared<UNOCard>(color, number));
    }
  }
  // clang-format on
  return std::shared_ptr<Deck>(new Deck(cards));
}

std::shared_ptr<Deck> Deck::CreatePokerDeck() {
  std::vector<std::shared_ptr<Card>> cards;
  // clang-format off
  for (auto rank : {Rank::kAce, Rank::kTwo, Rank::kThree, Rank::kFour, Rank::kFive,
                    Rank::kSix, Rank::kSeven, Rank::kEight, Rank::kNine, Rank::kTen,
                    Rank::kJack, Rank::kQueen, Rank::kKing}) {
    for (auto suit : {Suit::kClub, Suit::kDiamond, Suit::kHeart, Suit::kSpade}) {
      cards.push_back(std::make_shared<PokerCard>(suit, rank));
    }
  }
  // clang-format on
  return std::shared_ptr<Deck>(new Deck(cards));
}

void Deck::Shuffle() { std::ranges::shuffle(cards_, std::default_random_engine{}); }

std::shared_ptr<Card> Deck::Deal() {
  if (!cards_.size()) {
    throw std::out_of_range("No cards left in the deck");
  }
  auto card = cards_.back();
  cards_.pop_back();
  return card;
}

void Deck::AddCards(std::vector<std::shared_ptr<Card>> cards) {
  cards_.insert(cards_.end(), cards.begin(), cards.end());
}

bool Deck::IsEmpty() const { return cards_.empty(); }

Deck::Deck(std::vector<std::shared_ptr<Card>> cards) : cards_(cards) {}
