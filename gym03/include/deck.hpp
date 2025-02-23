#pragma once

#include <vector>

#include "card.hpp"

class Deck {
 public:
  static std::shared_ptr<Deck> CreateUNODeck();
  static std::shared_ptr<Deck> CreatePokerDeck();
  void Shuffle();
  std::shared_ptr<Card> Deal();
  void AddCards(std::vector<std::shared_ptr<Card>> cards);
  bool IsEmpty() const;

 private:
  explicit Deck(std::vector<std::shared_ptr<Card>> cards);
  std::vector<std::shared_ptr<Card>> cards_;
};
