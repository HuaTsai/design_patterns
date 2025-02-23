#include "card_game.hpp"

#include <iostream>

CardGame::CardGame(std::shared_ptr<Deck> deck, std::vector<std::shared_ptr<Player>> players,
                   int player_initial_cards)
    : deck_(deck), players_(players), player_initial_cards_(player_initial_cards) {}

void CardGame::PreparePhase() {
  deck_->Shuffle();
  for (auto player : players_) {
    player->NameSelf();
  }
}

void CardGame::DrawPhase() {
  for (auto player : players_) {
    for (int i = 0; i < player_initial_cards_; i++) {
      player->Draw(deck_);
    }
  }
}

void CardGame::ScorePhase() {
  int best_score = -1;
  for (auto player : players_) {
    best_score = std::max(best_score, player->points());
  }
  std::vector<std::string> winners;
  for (auto player : players_) {
    if (player->points() == best_score) {
      winners.push_back(player->name());
    }
  }
  if (winners.size() == 1) {
    std::cout << "\nThe winner is: " << winners[0] << std::endl;
  } else {
    std::cout << "\nThe winners are: ";
    for (size_t i = 0; i < winners.size(); i++) {
      std::cout << winners[i];
      if (i < winners.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
}
