#pragma once

#include "player.hpp"

class HumanPlayer : public Player {
 public:
  using Player::Player;
  void NameSelf() override;
  std::shared_ptr<Card> Show() override;
};
