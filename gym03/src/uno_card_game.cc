#include "uno_card_game.hpp"

#include <iostream>
#include <utility>

UNOCardGame::UNOCardGame(std::shared_ptr<Deck> deck, std::vector<std::shared_ptr<Player>> players)
    : CardGame(deck, players, kUNOInitialCards) {}

void UNOCardGame::PlayPhase() {
  const std::shared_ptr<Card> topcard = deck()->Deal();
  discard_cards_.push_back(topcard);

  for (const auto &player : players()) {
    player->UpdateTopCard(topcard);
  }

  std::cout << "\n";
  int i = 0;
  while (true) {
    auto card = players()[i]->Show();
    if (card) {
      std::cout << std::format("{} plays {}\n", players()[i]->name(), card);
      discard_cards_.push_back(card);
      for (const auto &player : players()) {
        player->UpdateTopCard(card);
      }
      if (players()[i]->IsEmptyHand()) {
        players()[i]->AddPoint();
        break;
      }
    } else {
      std::cout << std::format("{} has no card to play, draws a card\n", players()[i]->name());
      if (deck()->IsEmpty()) {
        std::cout << "Deck is empty, add discard cards and shuffle\n";
        auto newest_card = discard_cards_.back();  // save the newest card
        discard_cards_.pop_back();
        deck()->AddCards(discard_cards_);
        deck()->Shuffle();
        discard_cards_.clear();
        discard_cards_.push_back(newest_card);
      }
      players()[i]->Draw(deck());
    }

    ++i;
    if (std::cmp_equal(i, players().size())) {
      i = 0;
      std::cout << "\n";
    }
  }
}
