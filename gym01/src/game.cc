#include "game.hpp"

#include <algorithm>
#include <format>
#include <iostream>
#include <queue>
#include <random>

#include "ai_player.hpp"
#include "human_player.hpp"

Game::Game(std::shared_ptr<Deck> deck) : turn_(0), players_(kPlayers, nullptr), deck_(deck) {}

std::vector<std::shared_ptr<Player>> Game::players() { return players_; }

void Game::Start() {
  // Phase 1: Initialization
  // 1.1 Initialize Players
  std::cout << "Initialize Phase:\n\n";
  std::cout << "How many ai players (0~4): ";
  int ai_players;
  std::cin >> ai_players;
  if (ai_players < 0 || ai_players > kPlayers) {
    throw std::runtime_error("Wrong input, end program.");
  }

  for (int i = 0; i < kPlayers; ++i) {
    if (i < ai_players) {
      players_[i] = std::make_shared<AIPlayer>(shared_from_this());
    } else {
      players_[i] = std::make_shared<HumanPlayer>(shared_from_this());
    }
  }
  auto rng = std::default_random_engine(std::random_device{}());
  std::ranges::shuffle(players_, rng);

  for (int i = 0; i < kPlayers; ++i) {
    auto &player = *players_[i].get();  // avoid clang warning
    if (typeid(player) == typeid(AIPlayer)) {
      std::cout << std::format("Player {} is an AI Player, name it: ", i + 1);
    } else {
      std::cout << std::format("Player {} is a Human Player, name it: ", i + 1);
    }
    std::string name;
    std::cin >> name;
    players_[i]->set_name(name);
  }

  // 1.2 Shuffle Deck
  deck_->Shuffle();

  // Phase 2: Draw Cards
  std::cout << "\nDrawing Phase:\n";
  for (int i = 0; i < kTotalTurns; ++i) {
    std::cout << std::format("\nDrawing Turn {}\n", i + 1);
    for (int j = 0; j < kPlayers; ++j) {
      auto card = players_[j]->Draw(deck_);
      std::cout << std::format("Player {} ({}) draws {}\n", j + 1, players_[j]->name(), *card);
    }
  }

  // Phase 3: Playing
  std::cout << "\nPlaying Phase:\n";

  int turn = 0;
  bool finish = false;
  std::vector<bool> hasability(kPlayers, true);
  std::queue<std::pair<int, std::pair<int, int>>> exchange_queue;
  while (!finish) {
    ++turn;
    std::cout << std::format("\nTurn {}:\n", turn);

    int max_player = -1;
    std::shared_ptr<Card> max_card = nullptr;
    for (int i = 0; i < kPlayers; ++i) {
      auto player = players_[i];
      auto name = player->name();

      // 3.1 Decide Exchanges
      if (hasability[i]) {
        std::cout << std::format("Player {} ({}) can decide whether to exchange hands\n", i + 1,
                                 name);
        auto dicision = player->MakeExchangeDecision();
        if (dicision) {
          hasability[i] = false;
          exchange_queue.push({turn + 3, {i, dicision.value()}});
        }
      }

      // 3.2 Show Card
      auto card = player->Show();
      if (!max_card || (card && card > max_card)) {
        max_card = card;
        max_player = i;
      }
    }

    // 3.3 Add Point
    // Guard: they can make everyone not show card, but the game does not finish
    if (max_card) {
      std::cout << std::format("Player {} ({}) wins this turn, add one point.\n", max_player + 1,
                               players_[max_player]->name());
      players_[max_player]->AddOnePoint();
    } else {
      std::cout << "No maximum card exists\n";
    }

    // 3.4 Exchange back
    while (exchange_queue.size() && exchange_queue.front().first == turn) {
      auto [i, j] = exchange_queue.front().second;
      exchange_queue.pop();
      players_[i]->Exchange(players_[j]);
      std::cout << std::format(
          "Three turns passed, Player {} ({}) exchanges back with Player {} "
          "({})\n",
          i + 1, players_[i]->name(), j + 1, players_[j]->name());
    }

    finish = true;
    for (const auto &player : players_) {
      finish &= player->IsEmptyHand();
    }
  }

  // Phase 4: Scoring
  std::cout << "\nScoring Phase:\n\n";
  int winner_idx = -1, winner_score = -1;
  for (int i = 0; i < kPlayers; ++i) {
    std::cout << std::format("Player {} ({}): {}\n", i + 1, players_[i]->name(),
                             players_[i]->points());
    if (players_[i]->points() > winner_score) {
      winner_idx = i;
      winner_score = players_[i]->points();
    }
  }
  std::cout << std::format("The winner is player {} ({})\n", winner_idx + 1,
                           players_[winner_idx]->name());
}
