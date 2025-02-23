#include "uno_card_game.hpp"

#include <iostream>

UNOCardGame::UNOCardGame(std::shared_ptr<Deck> deck, std::vector<std::shared_ptr<Player>> players)
    : CardGame(deck, players, kUNOInitialCards) {}

void UNOCardGame::PlayPhase() {
  std::shared_ptr<Card> topcard = deck_->Deal();
  discard_cards_.push_back(topcard);

  for (auto player : players_) {
    player->UpdateTopCard(topcard);
  }

  std::cout << "\n";
  int i = 0;
  while (true) {
    auto card = players_[i]->Show();
    if (card) {
      std::cout << std::format("{} plays {}\n", players_[i]->name(), card);
      discard_cards_.push_back(card);
      for (auto player : players_) {
        player->UpdateTopCard(card);
      }
      if (players_[i]->IsEmptyHand()) {
        players_[i]->AddPoint();
        break;
      }
    } else {
      std::cout << std::format("{} has no card to play, draws a card\n", players_[i]->name());
      if (deck_->IsEmpty()) {
        std::cout << "Deck is empty, add discard cards and shuffle\n";
        auto newest_card = discard_cards_.back();  // save the newest card
        discard_cards_.pop_back();
        deck_->AddCards(discard_cards_);
        deck_->Shuffle();
        discard_cards_.clear();
        discard_cards_.push_back(newest_card);
      }
      players_[i]->Draw(deck_);
    }

    if (++i == static_cast<int>(players_.size())) {
      i = 0;
      std::cout << "\n";
    }
  }
}
