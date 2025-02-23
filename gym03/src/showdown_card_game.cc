#include "showdown_card_game.hpp"

#include <iostream>

ShowdownCardGame::ShowdownCardGame(std::shared_ptr<Deck> deck,
                                   std::vector<std::shared_ptr<Player>> players)
    : CardGame(deck, players, kShowdownInitialCards) {}

void ShowdownCardGame::PlayPhase() {
  for (int turn = 1; turn <= kShowdownTurns; ++turn) {
    std::vector<std::shared_ptr<Card>> cards;
    std::shared_ptr<Card> max_card = nullptr;
    int max_idx = -1;
    for (size_t i = 0; i < players_.size(); ++i) {
      auto card = players_[i]->Show();
      cards.push_back(card);
      if (!max_card || card > max_card) {
        max_card = card;
        max_idx = i;
      }
    }

    std::cout << std::format("\nTurn {}:\n", turn);
    for (size_t i = 0; i < players_.size(); ++i) {
      std::cout << std::format("{} plays {}{}\n", players_[i]->name(), cards[i],
                               (static_cast<int>(i) == max_idx ? "*" : ""));
    }
    players_[max_idx]->AddPoint();
  }
}
