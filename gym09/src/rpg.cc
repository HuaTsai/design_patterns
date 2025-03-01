#include <ai.hpp>
#include <hero.hpp>
#include <iostream>
#include <print>
#include <rpg.hpp>
#include <sstream>

namespace {
std::shared_ptr<Role> InputRole(std::shared_ptr<Troop> troop, bool is_hero,
                                const std::string &prefix, const std::string &input) {
  std::string name;
  int hp = 0;
  int mp = 0;
  int str = 0;
  std::stringstream ss(input);
  ss >> name >> hp >> mp >> str;
  std::shared_ptr<Role> role;
  if (is_hero) {
    role = std::make_shared<Hero>(troop, prefix + name, hp, mp, str);
  } else {
    role = std::make_shared<AI>(troop, prefix + name, hp, mp, str);
  }
  std::string skill;
  while (ss >> skill) {
    role->AddSkill(skill);
  }
  role->SetState(std::make_shared<NormalState>(role));
  return role;
}
}  // namespace

RPG::RPG() : is_game_over_(false), troop1_(nullptr), troop2_(nullptr) {}

void RPG::Initialize() {
  troop1_ = std::make_shared<Troop>();
  troop2_ = std::make_shared<Troop>();

  troop1_->set_enemy_troop(troop2_);
  troop2_->set_enemy_troop(troop1_);

  std::string input;
  std::getline(std::cin, input);
  if (input != "#軍隊-1-開始") {
    throw std::invalid_argument("輸入要從 #軍隊-1-開始 開始");
  }

  bool is_hero = true;
  std::getline(std::cin, input);
  while (input != "#軍隊-1-結束") {
    if (is_hero) {
      hero_ = InputRole(troop1_, is_hero, "[1]", input);
      troop1_->AddRole(hero_);
      is_hero = false;
    } else {
      troop1_->AddRole(InputRole(troop1_, is_hero, "[1]", input));
    }
    std::getline(std::cin, input);
  }

  std::getline(std::cin, input);
  if (input != "#軍隊-2-開始") {
    throw std::invalid_argument("輸入要從 #軍隊-2-開始 開始");
  }

  std::getline(std::cin, input);
  while (input != "#軍隊-2-結束") {
    troop2_->AddRole(InputRole(troop2_, is_hero, "[2]", input));
    std::getline(std::cin, input);
  }
}

bool RPG::IsGameOver() const {
  return hero_->IsDead() || troop1_->IsAnnihilated() || troop2_->IsAnnihilated();
}

void RPG::Battle() {
  for (size_t i = 0; i < troop1_->GetAllies().size(); ++i) {
    auto role = troop1_->GetAllies()[i];
    if (role->IsDead()) {
      continue;
    }

    std::println("輪到 {} (HP: {}, MP: {}, STR: {}, State: {})。", role->name(), role->hp(),
                 role->mp(), role->str(), role->StateName());
    role->Action();
    if (IsGameOver()) {
      return;
    }
  }

  for (size_t i = 0; i < troop2_->GetAllies().size(); ++i) {
    auto role = troop2_->GetAllies()[i];
    if (role->IsDead()) {
      continue;
    }

    std::println("輪到 {} (HP: {}, MP: {}, STR: {}, State: {})。", role->name(), role->hp(),
                 role->mp(), role->str(), role->StateName());
    role->Action();
    if (IsGameOver()) {
      return;
    }
  }
}

void RPG::ShowWinner() {
  if (hero_->IsDead()) {
    std::println("你失敗了！");
  } else {
    std::println("你獲勝了！");
  }
}
