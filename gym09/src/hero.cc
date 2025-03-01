#include <hero.hpp>
#include <iostream>
#include <print>
#include <sstream>

std::shared_ptr<Skill> Hero::S1Input() {
  auto allskills = skills();

  std::print("選擇行動：(0) 普通攻擊");
  for (size_t i = 0; i < allskills.size(); i++) {
    std::print(" ({}) {}", i + 1, allskills[i]->name());
  }
  std::println();

  int input = -1;
  std::cin >> input;
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
      std::cin >> input;
      continue;
    }

    return skill;
  }
}

std::shared_ptr<Role> Hero::S2Input(const std::vector<std::shared_ptr<Role>> &candidates) {
  if (candidates.size() == 1) {
    return candidates[0];
  }
  std::print("選擇 1 位目標:");
  for (size_t i = 0; i < candidates.size(); i++) {
    std::print(" ({}) {}", i, candidates[i]->name());
  }
  std::println();

  int ret = -1;
  std::cin >> ret;
  return candidates[ret];
}

std::vector<std::shared_ptr<Role>> Hero::S2InputMultiple(
    const std::vector<std::shared_ptr<Role>> &candidates, int slots) {
  if (static_cast<int>(candidates.size()) <= slots) {
    return candidates;
  }

  std::print("選擇 {} 位目標: ", slots);
  for (size_t i = 0; i < candidates.size(); ++i) {
    if (i + 1 == candidates.size()) {
      std::print("({}) {}", i, candidates[i]->name());
    } else {
      std::print("({}) {} ", i, candidates[i]->name());
    }
  }
  std::println();

  std::vector<std::shared_ptr<Role>> ret;
  ret.reserve(slots);

  std::string input;
  std::cin.ignore();
  std::getline(std::cin, input);
  std::stringstream ss(input);
  std::string token;
  while (std::getline(ss, token, ',')) {
    ret.emplace_back(candidates[std::stoi(token)]);
  }
  return ret;
}
