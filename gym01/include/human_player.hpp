#pragma once

#include "player.hpp"

class HumanPlayer : public Player {
 public:
  explicit HumanPlayer(std::weak_ptr<Game> game);
  std::optional<int> MakeExchangeDecision() override;
  std::shared_ptr<Card> Show() override;
};
