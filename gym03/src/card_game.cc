#include "card_game.hpp"

#include <iostream>

CardGame::CardGame(std::shared_ptr<Deck> deck, std::vector<std::shared_ptr<Player>> players,
                   int player_initial_cards)
    : deck_(deck), players_(players), player_initial_cards_(player_initial_cards) {}

void CardGame::PreparePhase() {
  deck_->Shuffle();
  for (const auto &player : players()) {
    player->NameSelf();
  }
}

void CardGame::DrawPhase() {
  for (const auto &player : players()) {
    for (int i = 0; i < player_initial_cards_; i++) {
      player->Draw(deck_);
    }
  }
}

void CardGame::ScorePhase() const {
  int best_score = -1;
  for (const auto &player : players()) {
    best_score = std::max(best_score, player->points());
  }
  std::vector<std::string> winners;
  for (const auto &player : players()) {
    if (player->points() == best_score) {
      winners.push_back(player->name());
    }
  }
  if (winners.size() == 1) {
    std::cout << "\nThe winner is: " << winners[0] << "\n";
  } else {
    std::cout << "\nThe winners are: ";
    for (size_t i = 0; i < winners.size(); i++) {
      std::cout << winners[i];
      if (i < winners.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "\n";
  }
}
