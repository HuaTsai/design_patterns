#include "human_player.hpp"

#include <print>
#include <unordered_set>

#include "game.hpp"

HumanPlayer::HumanPlayer(std::weak_ptr<Game> game) : Player(game) {}

std::optional<int> HumanPlayer::MakeExchangeDecision() {
  std::print("{}'s Decision (Y/N)? ", name());
  char c = 0;
  std::cin >> c;
  if (std::tolower(c) == 'y') {
    if (auto g = game()) {
      auto players = g->players();
      std::print("Which player do {} want to exchange hands?\n", name());

      std::unordered_set<int> options;
      for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].get() != this) {
          options.insert(static_cast<int>(i + 1));
          std::print("{}: {}\n", i + 1, players[i]->name());
        }
      }
      std::print("{}'s Option? ", name());

      int index = 0;
      std::cin >> index;
      if (!options.contains(index)) {
        throw std::runtime_error("Invalid option!");
      }

      Exchange(players[index - 1]);
      std::print("Exchange finished\n");
      return index - 1;
    }
    throw std::runtime_error("Cannot get game object");
  }
  if (std::tolower(c) == 'n') {
    return std::nullopt;
  }
  throw std::runtime_error("Invalid option!");
}

std::shared_ptr<Card> HumanPlayer::Show() {
  if (hand().empty()) {
    std::print("{} has no available card, skip\n", name());
    return nullptr;
  }
  std::print("{} chooses card:\n", name());
  for (size_t i = 0; i < hand().size(); ++i) {
    std::print("{}: {}\n", i + 1, *hand()[i]);
  }

  if (hand().size() == 1) {
    std::print("{}'s Decision (1)? ", name());
  } else {
    std::print("{}'s Decision (1~{})? ", name(), hand().size());
  }

  int idx = 0;
  std::cin >> idx;
  if (idx <= 0 || idx > static_cast<int>(hand().size())) {
    throw std::runtime_error("Invlaid option!");
  }

  auto ret = hand()[idx - 1];
  swap(hand()[idx - 1], hand().back());
  hand().pop_back();
  std::print("{} shows {}\n", name(), *ret);
  return ret;
}
