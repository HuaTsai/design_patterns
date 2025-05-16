#pragma once

#include <random>

#include "player.hpp"

class AIPlayer : public Player {
 public:
  explicit AIPlayer(std::weak_ptr<Game> game);
  std::optional<int> MakeExchangeDecision() override;
  std::shared_ptr<Card> Show() override;

 private:
  std::mt19937 rng_;
};
