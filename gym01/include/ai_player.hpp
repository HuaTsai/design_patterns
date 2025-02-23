#pragma once

#include <random>

#include "player.hpp"

class AIPlayer : public Player {
 public:
  AIPlayer(std::weak_ptr<Game> game);
  ~AIPlayer();
  std::optional<int> MakeExchangeDecision() override;
  std::shared_ptr<Card> Show() override;

 private:
  std::mt19937 rng_;
};
