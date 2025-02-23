#include "ai_player.hpp"

std::shared_ptr<CardPattern> AIPlayer::FirstPlay(bool /* club_three_required */) {
  throw std::runtime_error("AIPlayers are not supported now due to the complexity.");
}

std::shared_ptr<CardPattern> AIPlayer::FollowPlay(std::shared_ptr<CardPattern> /* top_play */) {
  throw std::runtime_error("AIPlayers are not supported now due to the complexity.");
}
