#include <ai.hpp>
#include <print>

AI::AI(std::shared_ptr<Troop> troop, std::string name, int hp, int mp, int str)
    : Role(troop, name, hp, mp, str), seed_(0) {}

std::shared_ptr<Skill> AI::S1Input() {
  auto allskills = skills();
  const int options = 1 + static_cast<int>(allskills.size());

  std::print("選擇行動：(0) 普通攻擊");
  for (size_t i = 0; i < allskills.size(); i++) {
    std::print(" ({}) {}", i + 1, allskills[i]->name());
  }
  std::println();

  int input = seed_++ % options;
  while (true) {
    if (input == 0) {
      return nullptr;
    }

    const auto &skill = allskills[input - 1];
    if (skill->mp_cost() > mp()) {
      std::println("你缺乏 MP，不能進行此行動。");

      std::print("選擇行動：(0) 普通攻擊");
      for (size_t i = 0; i < allskills.size(); i++) {
        std::print(" ({}) {}", i + 1, allskills[i]->name());
      }
      std::println();

      input = seed_++ % options;
      continue;
    }

    return skill;
  }
}

std::shared_ptr<Role> AI::S2Input(const std::vector<std::shared_ptr<Role>> &candidates) {
  if (candidates.size() == 1) {
    return candidates[0];
  }
  return candidates[seed_++ % candidates.size()];
}

std::vector<std::shared_ptr<Role>> AI::S2InputMultiple(
    const std::vector<std::shared_ptr<Role>> &candidates, int slots) {
  if (static_cast<int>(candidates.size()) <= slots) {
    return candidates;
  }
  std::vector<std::shared_ptr<Role>> ret;
  ret.reserve(slots);
  for (int i = 0; i < slots; ++i) {
    ret.emplace_back(candidates[(seed_ + i) % candidates.size()]);
  }
  return ret;
}
