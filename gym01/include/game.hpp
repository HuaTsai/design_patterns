#pragma once

#include "player.hpp"

class Game : public std::enable_shared_from_this<Game> {
  constexpr static int kPlayers = 4;
  constexpr static int kTotalTurns = 13;

 public:
  explicit Game(std::shared_ptr<Deck> deck);
  void Start();
  std::vector<std::shared_ptr<Player>> players();

 private:
  void InitializePlayers();
  void DrawCards();
  void PlayGame();
  void ShowScores();

  int turn_;
  std::vector<std::shared_ptr<Player>> players_;
  std::shared_ptr<Deck> deck_;
};
