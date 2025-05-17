#include "showdown_card_game.hpp"

#include <iostream>
#include <utility>

ShowdownCardGame::ShowdownCardGame(std::shared_ptr<Deck> deck,
                                   std::vector<std::shared_ptr<Player>> players)
    : CardGame(deck, players, kShowdownInitialCards) {}

void ShowdownCardGame::PlayPhase() {
  for (int turn = 1; turn <= kShowdownTurns; ++turn) {
    std::vector<std::shared_ptr<Card>> cards;
    std::shared_ptr<Card> max_card = nullptr;
    int max_idx = -1;
    for (size_t i = 0; i < players().size(); ++i) {
      auto card = players()[i]->Show();
      cards.push_back(card);
      if (!max_card || card > max_card) {
        max_card = card;
        max_idx = static_cast<int>(i);
      }
    }

    std::cout << std::format("\nTurn {}:\n", turn);
    for (size_t i = 0; i < players().size(); ++i) {
      std::cout << std::format("{} plays {}{}\n", players()[i]->name(), cards[i],
                               (std::cmp_equal(i, max_idx) ? "*" : ""));
    }
    players()[max_idx]->AddPoint();
  }
}
