#pragma once

#include "card_pattern.hpp"
#include "deck.hpp"
#include "player.hpp"

class Big2 {
 public:
  void GameStart();
  void PrepareDeck();
  void PrepareSuffledDeck();
  void EnterNames();
  void ShuffleCards();
  void DealCards();
  void RoundStart();
  void ShowWinner() const;

 private:
  std::vector<std::shared_ptr<Player>> players_;
  std::shared_ptr<Deck> deck_;

  std::shared_ptr<CardPattern> top_play_;
  std::shared_ptr<Player> top_player_;
  std::shared_ptr<Player> winner_;
  std::shared_ptr<CardPatternRecognizer> recognizer_;
};
