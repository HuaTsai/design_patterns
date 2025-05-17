#include "ai_player.hpp"

#include "game.hpp"

AIPlayer::AIPlayer(std::weak_ptr<Game> game) : Player(game), rng_(std::random_device{}()) {}

std::optional<int> AIPlayer::MakeExchangeDecision() {
  std::cout << "AI making decision... ";
  std::uniform_int_distribution dis(0, 1);
  if (dis(rng_) == 0) {
    std::cout << "do not exchange\n";
    return std::nullopt;
  }
  std::cout << "do exchange\n";
  auto g = game();
  if (!g) {
    throw std::runtime_error("Cannot get game object");
  }
  auto players = g->players();
  std::vector<std::pair<int, std::shared_ptr<Player>>> options;
  for (size_t i = 0; i < players.size(); ++i) {
    if (players[i].get() != this) {
      options.emplace_back(i, players[i]);
    }
  }
  std::uniform_int_distribution dis2(0, static_cast<int>(options.size()) - 1);
  auto [id, player] = options[dis2(rng_)];
  std::cout << std::format("Exchange with player {} ({})\n", id + 1, player->name());
  Exchange(player);
  return id;
}

std::shared_ptr<Card> AIPlayer::Show() {
  if (hand().empty()) {
    std::cout << std::format("{} has no available card, skip\n", name());
    return nullptr;
  }
  std::cout << std::format("{} chooses card, AI making decision...\n", name());
  std::uniform_int_distribution dis(0, static_cast<int>(hand().size()) - 1);
  const int idx = dis(rng_);

  auto ret = hand()[idx];
  swap(hand()[idx], hand().back());
  hand().pop_back();
  std::cout << std::format("{} shows {}\n", name(), *ret);
  return ret;
}
