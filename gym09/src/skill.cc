#include <functional>
#include <print>
#include <skill.hpp>
#include <slime.hpp>
#include <troop.hpp>

std::shared_ptr<Skill> Skill::Create(const std::string &name, std::shared_ptr<Role> role) {
  // clang-format off
  static const std::unordered_map<std::string, std::function<std::shared_ptr<Skill>(std::shared_ptr<Role>)>> creation_map{
    {WaterballSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<WaterballSkill>(role); }},
    {FireballSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<FireballSkill>(role); }},
    {SelfHealingSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<SelfHealingSkill>(role); }},
    {PetrochemicalSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<PetrochemicalSkill>(role); }},
    {PoisonSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<PoisonSkill>(role); }},
    {SummonSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<SummonSkill>(role); }},
    {SelfExplosionSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<SelfExplosionSkill>(role); }},
    {CheerupSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<CheerupSkill>(role); }},
    {CurseSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<CurseSkill>(role); }},
    {OnePunchSkill::name(), [](std::shared_ptr<Role> role) { return std::make_shared<OnePunchSkill>(role); }},
  };
  // clang-format on

  if (!creation_map.count(name)) {  // NOLINT
    throw std::invalid_argument("技能不存在");
  }

  return creation_map.at(name)(role);
}

std::vector<std::shared_ptr<Role>> OneEnemySkill::RequestForTargets() {
  auto candidates = role()->troop()->GetAliveEnemies();
  if (candidates.size() == 1) {
    return candidates;
  }
  return {role()->S2Input(candidates)};
}

void WaterballSkill::PerformSkill() {
  const int damage = 120;
  auto targets = RequestForTargets();
  std::print("{} 對 {} 使用了 {}。\n", role()->name(), targets[0]->name(), name());
  role()->Attack(targets[0], damage);
  role()->ConsumeMp(mp_cost());
}

void FireballSkill::PerformSkill() {
  auto targets = role()->troop()->GetAliveEnemies();
  const int damage = 50;
  std::print("{} 對 ", role()->name());
  for (size_t i = 0; i < targets.size(); i++) {
    if (i + 1 == targets.size()) {
      std::print("{}", targets[i]->name());
    } else {
      std::print("{}, ", targets[i]->name());
    }
  }
  std::print(" 使用了 {}。\n", name());
  for (const auto &target : targets) {
    role()->Attack(target, damage);
  }
  role()->ConsumeMp(mp_cost());
}

void SelfHealingSkill::PerformSkill() {
  const int heal = 150;
  std::print("{} 使用了 {}。\n", role()->name(), name());
  role()->Heal(heal);
  role()->ConsumeMp(mp_cost());
}

void PetrochemicalSkill::PerformSkill() {
  auto targets = RequestForTargets();
  std::print("{} 對 {} 使用了 {}。\n", role()->name(), targets[0]->name(), name());
  targets[0]->SetState(std::make_shared<PetrochemicalState>(targets[0]));
  role()->ConsumeMp(mp_cost());
}

void PoisonSkill::PerformSkill() {
  auto targets = RequestForTargets();
  std::print("{} 對 {} 使用了 {}。\n", role()->name(), targets[0]->name(), name());
  targets[0]->SetState(std::make_shared<PoisonedState>(targets[0]));
  role()->ConsumeMp(mp_cost());
}

void SummonSkill::PerformSkill() {
  std::print("{} 使用了 {}。\n", role()->name(), name());
  const std::string prefix = role()->name().substr(0, 3);
  auto slime = std::make_shared<Slime>(role()->troop(), prefix + "Slime", role());
  slime->SetState(std::make_shared<NormalState>(slime));
  role()->troop()->AddRole(slime);
  role()->ConsumeMp(mp_cost());
}

void SelfExplosionSkill::PerformSkill() {
  std::vector<std::shared_ptr<Role>> targets;
  auto allies = role()->troop()->GetAliveAllies();
  for (const auto &ally : allies) {
    if (ally.get() == role().get()) {
      continue;
    }
    targets.emplace_back(ally);
  }
  auto enemies = role()->troop()->GetAliveEnemies();
  targets.insert(targets.end(), enemies.begin(), enemies.end());

  const int damage = 150;
  std::print("{} 對 ", role()->name());
  for (size_t i = 0; i < targets.size(); i++) {
    if (i + 1 == targets.size()) {
      std::print("{}", targets[i]->name());
    } else {
      std::print("{}, ", targets[i]->name());
    }
  }
  std::print(" 使用了 {}。\n", name());
  for (const auto &target : targets) {
    role()->Attack(target, damage);
  }
  role()->ConsumeMp(mp_cost());
  role()->TakeDamage(role()->hp());
}

void CheerupSkill::PerformSkill() {
  auto targets = role()->troop()->GetAliveAllies();
  std::erase_if(targets, [this](const auto &ally) { return ally == role(); });
  if (targets.size() > 3) {
    targets = role()->S2InputMultiple(targets, 3);
  }

  if (targets.empty()) {
    std::print("{} 使用了 {}。\n", role()->name(), name());
    role()->ConsumeMp(mp_cost());
    return;
  }

  if (targets.size() > 3) {
    throw std::invalid_argument("鼓舞技能只能對一到三個友軍使用");
  }

  std::print("{} 對 ", role()->name());
  for (size_t i = 0; i < targets.size(); i++) {
    if (i + 1 == targets.size()) {
      std::print("{}", targets[i]->name());
    } else {
      std::print("{}, ", targets[i]->name());
    }
  }
  std::print(" 使用了 {}。\n", name());
  for (const auto &target : targets) {
    target->SetState(std::make_shared<CheerupState>(target));
  }
  role()->ConsumeMp(mp_cost());
}

void CurseSkill::PerformSkill() {
  auto targets = RequestForTargets();
  std::print("{} 對 {} 使用了 {}。\n", role()->name(), targets[0]->name(), name());
  targets[0]->AddCurser(role());
  role()->ConsumeMp(mp_cost());
}

void OnePunchSkill::PerformSkill() {
  auto targets = RequestForTargets();
  std::print("{} 對 {} 使用了 {}。\n", role()->name(), targets[0]->name(), name());
  // NOLINTBEGIN
  if (targets[0]->hp() >= 500) {
    role()->Attack(targets[0], 300);
  } else if (typeid(*targets[0]->state()) == typeid(PoisonedState) ||
             typeid(*targets[0]->state()) == typeid(PetrochemicalState)) {
    for (int i = 0; i < 3 && targets[0]->IsAlive(); ++i) {
      role()->Attack(targets[0], 80);
    }
  } else if (typeid(*targets[0]->state()) == typeid(CheerupState)) {
    role()->Attack(targets[0], 100);
    targets[0]->SetState(std::make_shared<NormalState>(targets[0]));
  } else {
    role()->Attack(targets[0], 100);
  }
  // NOLINTEND
  role()->ConsumeMp(mp_cost());
}
