#include <iostream>
#include <role.hpp>
#include <state.hpp>

std::shared_ptr<State> State::CreateStateFromTreasure(const std::shared_ptr<Treasure> &treasure,
                                                      const std::shared_ptr<Role> &role) {
  if (dynamic_pointer_cast<SuperStar>(treasure)) {
    return std::make_shared<InvincibleState>(role);
  }

  if (dynamic_pointer_cast<Poison>(treasure)) {
    return std::make_shared<PoisonedState>(role);
  }

  if (dynamic_pointer_cast<AcceleratingPotion>(treasure)) {
    return std::make_shared<AcceleratedState>(role);
  }

  if (dynamic_pointer_cast<HealingPotion>(treasure)) {
    return std::make_shared<HealingState>(role);
  }

  if (dynamic_pointer_cast<DevilFruit>(treasure)) {
    return std::make_shared<OrderlessState>(role);
  }

  if (dynamic_pointer_cast<KingsRock>(treasure)) {
    return std::make_shared<StockpileState>(role);
  }

  if (dynamic_pointer_cast<DokodemoDoor>(treasure)) {
    return std::make_shared<TeleportState>(role);
  }

  return std::make_shared<NormalState>(role);
}

State::State(const std::shared_ptr<Role> &role, std::string name, int remaining_turns)
    : role_(role),
      name_(std::move(name)),
      remaining_turns_(remaining_turns),
      pending_state_(nullptr) {}

void State::RoundStartEvent() {}

void State::HandleDamage(int hp) { role_.lock()->Damage(hp); }

std::shared_ptr<State> State::RoundEndEvent() {
  if (pending_state_) {
    return pending_state_;
  }

  if (--remaining_turns_ == 0) {
    return std::make_shared<NormalState>(role_.lock());
  }
  return nullptr;
}

void State::SetPendingState(const std::shared_ptr<State> &state) { pending_state_ = state; }

void InvincibleState::HandleDamage(int /* hp */) {}

void PoisonedState::RoundStartEvent() { role()->Damage(kDamageEachRound); }

void AcceleratedState::HandleDamage(int hp) {
  State::HandleDamage(hp);
  SetPendingState(std::make_shared<NormalState>(role()));
}

void HealingState::RoundStartEvent() { role()->Heal(kHealingEachRound); }

std::shared_ptr<State> HealingState::RoundEndEvent() {
  if (role()->IsFullHealth()) {
    return std::make_shared<NormalState>(role());
  }
  return State::RoundEndEvent();
}

void StockpileState::HandleDamage(int hp) {
  State::HandleDamage(hp);
  SetPendingState(std::make_shared<NormalState>(role()));
}

std::shared_ptr<State> StockpileState::RoundEndEvent() {
  if (pending_state()) {
    return pending_state();
  }
  set_remaining_turns(remaining_turns() - 1);
  if (remaining_turns() == 0) {
    return std::make_shared<EruptingState>(role());
  }
  return nullptr;
}

std::shared_ptr<State> EruptingState::RoundEndEvent() {
  if (pending_state()) {
    return pending_state();
  }
  set_remaining_turns(remaining_turns() - 1);
  if (remaining_turns() == 0) {
    return std::make_shared<TeleportState>(role());
  }
  return nullptr;
}

// void TeleportState::RoundStartEvent() {
//   auto [x, y] = role()->GetRandomEmptyPosition();
//   role()->MoveTo(x, y);
// }
