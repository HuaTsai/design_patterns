#include "human_player.hpp"

#include <unordered_set>

#include "game.hpp"

HumanPlayer::HumanPlayer(std::weak_ptr<Game> game) : Player(game) {}

std::optional<int> HumanPlayer::MakeExchangeDecision() {
  std::cout << std::format("{}'s Decision (Y/N)? ", name());
  char c;
  std::cin >> c;
  if (std::tolower(c) == 'y') {
    if (auto g = game()) {
      auto players = g->players();
      std::cout << std::format("Which player do {} want to exchange hands?\n", name());

      std::unordered_set<int> options;
      for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].get() != this) {
          options.insert(i + 1);
          std::cout << std::format("{}: {}\n", i + 1, players[i]->name());
        }
      }
      std::cout << std::format("{}'s Option? ", name());

      int index;
      std::cin >> index;
      if (!options.contains(index)) {
        throw std::runtime_error("Invalid option!");
      }

      Exchange(players[index - 1]);
      std::cout << "Exchange finished\n";
      return index - 1;
    } else {
      throw std::runtime_error("Cannot get game object");
    }
  } else if (std::tolower(c) == 'n') {
    return std::nullopt;
  } else {
    throw std::runtime_error("Invalid option!");
  }
}

std::shared_ptr<Card> HumanPlayer::Show() {
  if (!hand().size()) {
    std::cout << std::format("{} has no available card, skip\n", name());
    return nullptr;
  }
  std::cout << std::format("{} chooses card:\n", name());
  for (size_t i = 0; i < hand().size(); ++i) {
    std::cout << std::format("{}: {}\n", i + 1, *hand()[i]);
  }

  if (hand().size() == 1) {
    std::cout << std::format("{}'s Decision (1)? ", name());
  } else {
    std::cout << std::format("{}'s Decision (1~{})? ", name(), hand().size());
  }

  int idx;
  std::cin >> idx;
  if (idx <= 0 || idx > static_cast<int>(hand().size())) {
    throw std::runtime_error("Invlaid option!");
  }

  auto ret = hand()[idx - 1];
  swap(hand()[idx - 1], hand().back());
  hand().pop_back();
  std::cout << std::format("{} shows {}\n", name(), *ret);
  return ret;
}
