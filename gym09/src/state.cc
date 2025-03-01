#include <print>
#include <state.hpp>
#include <troop.hpp>

State::State(std::string name, std::shared_ptr<Role> role, int remain_turns)
    : name_(name), role_(role), remain_turns_(remain_turns), next_state_(nullptr) {}

void State::Action() {
  ActionStartEvent();

  if (role()->IsDead()) {
    return;
  }

  auto act = role()->S1Input();
  if (!act) {
    auto candidates = role()->troop()->GetAliveEnemies();
    if (candidates.size() == 1) {
      role()->BasicAttack(candidates[0]);
    } else {
      auto target = role()->S2Input(candidates);
      role()->BasicAttack(target);
    }
  } else {
    act->PerformSkill();
  }

  ActionEndEvent();
}

void State::Attack(std::shared_ptr<Role> target, int hp) {
  std::println("{} 對 {} 造成 {} 點傷害。", role()->name(), target->name(), hp);
  target->TakeDamage(hp);
}

void State::ActionStartEvent() {}

void State::ActionEndEvent() {
  if (remain_turns_ > 0) {
    --remain_turns_;
    if (remain_turns_ == 0) {
      next_state_ = std::make_shared<NormalState>(role());
    }
  }
}

std::string State::name() const { return name_; }

std::shared_ptr<Role> State::role() const { return role_.lock(); }

std::shared_ptr<State> State::next_state() const { return next_state_; }

NormalState::NormalState(std::shared_ptr<Role> role) : State("正常", role, -1) {}

PetrochemicalState::PetrochemicalState(std::shared_ptr<Role> role) : State("石化", role, 3) {}

void PetrochemicalState::Action() { ActionEndEvent(); }

PoisonedState::PoisonedState(std::shared_ptr<Role> role) : State("中毒", role, 3) {}

void PoisonedState::ActionStartEvent() { role()->TakeDamage(kActionStartDamage); }

CheerupState::CheerupState(std::shared_ptr<Role> role) : State("受到鼓舞", role, 3) {}

void CheerupState::Attack(std::shared_ptr<Role> target, int hp) {
  State::Attack(target, hp + kBonusDamage);
}
