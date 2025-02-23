#pragma once

#include "player.hpp"

class AIPlayer : public Player {
 public:
  using Player::Player;
  std::shared_ptr<CardPattern> FirstPlay(bool club_three_required = false) override;
  std::shared_ptr<CardPattern> FollowPlay(std::shared_ptr<CardPattern> top_play) override;
};
