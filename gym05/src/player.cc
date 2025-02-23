#include "player.hpp"

#include <algorithm>
#include <iostream>

Player::Player(std::string name, std::shared_ptr<CardPatternRecognizer> recognizer)
    : name_(name), recognizer_(recognizer) {}

void Player::AddCard(std::shared_ptr<Card> card) {
  hand_cards_.push_back(card);
  std::ranges::sort(hand_cards_, [](auto a, auto b) { return *a < *b; });
}

bool Player::HasClubThreeInHand() {
  return std::ranges::any_of(hand_cards_, [](auto card) {
    return card->suit() == Suit::kClubs && card->rank() == Rank::kThree;
  });
}

bool Player::IsEmptyHandCards() const { return hand_cards_.empty(); }

void Player::PrintHandCards() const {
  std::string nums;
  for (size_t i = 0; i < hand_cards_.size(); ++i) {
    std::string num = std::to_string(i);
    int pad = hand_cards_[i]->string().size() - num.size();
    if (i + 1 != hand_cards_.size()) {
      nums += num + std::string(pad + 1, ' ');
    } else {
      nums += num + "\n";
    }
  }

  std::string cards;
  for (auto card : hand_cards_) {
    if (card != hand_cards_.back()) {
      cards += card->string() + " ";
    } else {
      cards += card->string() + "\n";
    }
  }

  std::cout << nums << cards;
}

std::string Player::name() const { return name_; }
