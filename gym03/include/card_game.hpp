#pragma once

#include "deck.hpp"
#include "player.hpp"

class CardGame {
 public:
  CardGame(std::shared_ptr<Deck> deck, std::vector<std::shared_ptr<Player>> players,
           int player_initial_cards);

  virtual ~CardGame() = default;
  CardGame(const CardGame &) = delete;
  CardGame &operator=(const CardGame &) = delete;
  CardGame(CardGame &&) = delete;
  CardGame &operator=(CardGame &&) = delete;

  void PreparePhase();
  void DrawPhase();
  virtual void PlayPhase() = 0;
  void ScorePhase() const;

  std::vector<std::shared_ptr<Player>> players() const { return players_; }
  std::shared_ptr<Deck> deck() const { return deck_; }

 private:
  std::shared_ptr<Deck> deck_;
  std::vector<std::shared_ptr<Player>> players_;
  int player_initial_cards_;
};
