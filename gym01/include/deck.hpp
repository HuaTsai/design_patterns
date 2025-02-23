#pragma once

#include <memory>
#include <vector>

#include "card.hpp"

class Deck {
  static constexpr int kNumOfRanks = 13;

 public:
  Deck();
  void Shuffle();
  std::shared_ptr<Card> Deal();

 private:
  std::vector<std::shared_ptr<Card>> cards_;
};
