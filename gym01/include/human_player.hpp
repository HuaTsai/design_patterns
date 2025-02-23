#pragma once

#include "player.hpp"

class HumanPlayer : public Player {
 public:
  HumanPlayer(std::weak_ptr<Game> game);
  ~HumanPlayer();
  std::optional<int> MakeExchangeDecision() override;
  std::shared_ptr<Card> Show() override;
};
