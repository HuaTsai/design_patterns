#pragma once

#include "deck.hpp"
#include "player.hpp"

class CardGame {
 public:
  CardGame(std::shared_ptr<Deck> deck, std::vector<std::shared_ptr<Player>> players,
           int player_initial_cards);
  virtual ~CardGame() = default;
  void PreparePhase();
  void DrawPhase();
  virtual void PlayPhase() = 0;
  void ScorePhase();

 protected:
  std::shared_ptr<Deck> deck_;
  std::vector<std::shared_ptr<Player>> players_;
  int player_initial_cards_;
};
