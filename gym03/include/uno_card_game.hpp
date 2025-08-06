#pragma once

#include "card_game.hpp"

class UNOCardGame : public CardGame {
  static constexpr int kUNOInitialCards = 5;

 public:
  UNOCardGame(std::shared_ptr<Deck> deck, const std::vector<std::shared_ptr<Player>> &players);

  void PlayPhase() override;

 private:
  std::vector<std::shared_ptr<Card>> discard_cards_;
};
