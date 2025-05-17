#include "ai_player.hpp"

#include <iostream>
#include <random>

#include "uno_card.hpp"

namespace {
const std::array<std::string_view, 19> name_candidates = {
    "Liam", "Noah", "Ryan", "Luke", "Evan", "Adam", "Jake", "Alex", "Sean", "Emma",
    "Lily", "Mia",  "Zoe",  "Anna", "Ruby", "Eva",  "Kate", "Nora", "Jane",
};
}  // namespace

void AIPlayer::NameSelf() {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, static_cast<int>(name_candidates.size()) - 1);
  set_name(name_candidates.at(dis(gen)));
  std::cerr << "AI chooses name " << name() << "\n";
}

std::shared_ptr<Card> AIPlayer::Show() {
  std::vector<std::shared_ptr<Card>> options;
  for (auto &card : hand()) {
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

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution dis(0, static_cast<int>(options.size()) - 1);
  const int idx = dis(gen);
  auto ret = options[idx];
  std::erase(hand(), ret);
  return ret;
}
