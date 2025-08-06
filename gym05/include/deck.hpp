#pragma once

#include <vector>

#include "card.hpp"

class Deck {
 public:
  Deck();
  explicit Deck(const std::vector<std::shared_ptr<Card>> &cards);
  void Shuffle();
  std::shared_ptr<Card> Deal();
  bool IsEmpty();

 private:
  std::vector<std::shared_ptr<Card>> cards_;
};
