#pragma once

#include "card_game.hpp"

class ShowdownCardGame : public CardGame {
  static constexpr int kShowdownInitialCards = 13;
  static constexpr int kShowdownTurns = 13;

 public:
  ShowdownCardGame(std::shared_ptr<Deck> deck, const std::vector<std::shared_ptr<Player>> &players);

  void PlayPhase() override;
};
