#include "ai_player.hpp"

#include "game.hpp"

AIPlayer::AIPlayer(std::weak_ptr<Game> game) : Player(game), rng_(std::random_device{}()) {}

AIPlayer::~AIPlayer() {}

std::optional<int> AIPlayer::MakeExchangeDecision() {
  std::cout << "AI making decision... ";
  std::uniform_int_distribution<> dis(0, 1);
  if (dis(rng_)) {
    std::cout << "do exchange\n";
    if (auto game = game_.lock()) {
      auto players = game->players();
      std::vector<std::pair<int, std::shared_ptr<Player>>> options;
      for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].get() != this) {
          options.push_back({i, players[i]});
        }
      }
      std::uniform_int_distribution<> dis(0, static_cast<int>(options.size()) - 1);
      auto [id, player] = options[dis(rng_)];
      std::cout << std::format("Exchange with player {} ({})\n", id + 1, player->name());
      Exchange(player);
      return id;
    } else {
      throw std::runtime_error("Cannot get game object");
    }
  } else {
    std::cout << "do not exchange\n";
    return std::nullopt;
  }
}

std::shared_ptr<Card> AIPlayer::Show() {
  if (!hand_.size()) {
    std::cout << std::format("{} has no available card, skip\n", name_);
    return nullptr;
  }
  std::cout << std::format("{} chooses card, AI making decision...\n", name_);
  std::uniform_int_distribution<> dis(0, static_cast<int>(hand_.size()) - 1);
  int idx = dis(rng_);

  auto ret = hand_[idx];
  swap(hand_[idx], hand_.back());
  hand_.pop_back();
  std::cout << std::format("{} shows {}\n", name_, *ret);
  return ret;
}
