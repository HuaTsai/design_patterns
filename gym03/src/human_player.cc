#include "human_player.hpp"

#include <iostream>
#include <utility>

#include "uno_card.hpp"

void HumanPlayer::NameSelf() {
  std::string name;
  std::cout << "Enter player's name? ";
  std::cin >> name;
  std::cout << "OKay\n";
  set_name(name);
}

std::shared_ptr<Card> HumanPlayer::Show() {
  std::vector<std::shared_ptr<Card>> options;
  for (const auto &card : hand()) {
    if (type() == Player::Type::kUNO) {
      auto unocard = dynamic_pointer_cast<UNOCard>(card);
      auto tpcard = dynamic_pointer_cast<UNOCard>(topcard());
      if (!unocard->HasSameColorOrNumber(*tpcard)) {
        continue;
      }
    }
    options.push_back(card);
  }

  if (options.empty()) {
    return nullptr;
  }

  std::cout << std::format("\n{}'s hand:\n", name());
  for (size_t i = 0; i < options.size(); ++i) {
    std::cout << std::format("{}) {}\n", i + 1, options[i]);
  }
  std::cout << std::format("? (1-{}) ", options.size());
  int idx = 0;
  std::cin >> idx;
  if (idx < 1 || std::cmp_greater(idx, options.size())) {
    throw std::runtime_error("Invalid input");
  }
  auto ret = options[idx - 1];
  std::erase(hand(), ret);
  return ret;
}
