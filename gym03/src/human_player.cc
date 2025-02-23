#include "human_player.hpp"

#include <iostream>

#include "uno_card.hpp"

void HumanPlayer::NameSelf() {
  std::string name;
  std::cout << "Enter player's name? ";
  std::cin >> name;
  std::cout << "OKay\n";
  name_ = name;
}

std::shared_ptr<Card> HumanPlayer::Show() {
  std::vector<std::shared_ptr<Card>> options;
  for (auto card : hand_) {
    if (type_ == Player::Type::kUNO) {
      auto unocard = dynamic_pointer_cast<UNOCard>(card);
      auto topcard = dynamic_pointer_cast<UNOCard>(topcard_);
      if (!unocard->HasSameColorOrNumber(*topcard)) continue;
    }
    options.push_back(card);
  }

  if (!options.size()) return nullptr;

  std::cout << std::format("\n{}'s hand:\n", name_);
  for (size_t i = 0; i < options.size(); ++i)
    std::cout << std::format("{}) {}\n", i + 1, options[i]);
  std::cout << std::format("? (1-{}) ", options.size());
  int idx;
  std::cin >> idx;
  if (idx < 1 || idx > static_cast<int>(options.size())) {
    throw std::runtime_error("Invalid input");
  }
  auto ret = options[idx - 1];
  std::erase(hand_, ret);
  return ret;
}
