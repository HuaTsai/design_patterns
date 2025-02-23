#include "ai_player.hpp"

#include <iostream>
#include <random>

#include "uno_card.hpp"

namespace {
std::vector<std::string> name_candidates = {
    "Liam", "Noah", "Ryan", "Luke", "Evan", "Adam", "Jake", "Alex", "Sean", "Emma",
    "Lily", "Mia",  "Zoe",  "Anna", "Ruby", "Eva",  "Kate", "Nora", "Jane",
};
}  // namespace

void AIPlayer::NameSelf() {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, static_cast<int>(name_candidates.size()) - 1);
  name_ = name_candidates[dis(gen)];
  std::cerr << "AI chooses name " << name_ << "\n";
}

std::shared_ptr<Card> AIPlayer::Show() {
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

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, static_cast<int>(options.size()) - 1);
  int idx = dis(gen);
  auto ret = options[idx];
  std::erase(hand_, ret);
  return ret;
}
