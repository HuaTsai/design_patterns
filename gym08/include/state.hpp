#pragma once

#include <string>
#include <treasure.hpp>

class Role;

class State {
 public:
  static std::shared_ptr<State> CreateStateFromTreasure(const std::shared_ptr<Treasure> &treasure,
                                                        const std::shared_ptr<Role> &role);
  explicit State(const std::shared_ptr<Role> &role, const std::string &name, int remaining_turns);

  virtual ~State() = default;
  State(const State &) = delete;
  State &operator=(const State &) = delete;
  State(State &&) = delete;
  State &operator=(State &&) = delete;

  virtual void RoundStartEvent();
  virtual void HandleDamage(int hp);
  virtual std::shared_ptr<State> RoundEndEvent();
  void SetPendingState(const std::shared_ptr<State> &state);

  [[nodiscard]] std::shared_ptr<Role> role() const { return role_.lock(); }
  [[nodiscard]] std::string name() const { return name_; }
  [[nodiscard]] int remaining_turns() const { return remaining_turns_; }
  void set_remaining_turns(int remaining_turns) { remaining_turns_ = remaining_turns; }
  [[nodiscard]] std::shared_ptr<State> pending_state() const { return pending_state_; }

 private:
  std::weak_ptr<Role> role_;
  std::string name_;
  int remaining_turns_ = 0;
  std::shared_ptr<State> pending_state_;
};

class NormalState : public State {
  constexpr static int kRemainingTurns = -1;

 public:
  explicit NormalState(const std::shared_ptr<Role> &role)
      : State(role, "Normal", kRemainingTurns) {}
};

class InvincibleState : public State {
  constexpr static int kRemainingTurns = 2;

 public:
  explicit InvincibleState(const std::shared_ptr<Role> &role)
      : State(role, "Invincible", kRemainingTurns) {}
  void HandleDamage(int hp) override;
};

class PoisonedState : public State {
  constexpr static int kRemainingTurns = 3;
  constexpr static int kDamageEachRound = 15;

 public:
  explicit PoisonedState(const std::shared_ptr<Role> &role)
      : State(role, "Poisoned", kRemainingTurns) {}
  void RoundStartEvent() override;
};

class AcceleratedState : public State {
  constexpr static int kRemainingTurns = 3;

 public:
  explicit AcceleratedState(const std::shared_ptr<Role> &role)
      : State(role, "Accelerated", kRemainingTurns) {}
  void HandleDamage(int hp) override;
};

class HealingState : public State {
  constexpr static int kRemainingTurns = 5;
  constexpr static int kHealingEachRound = 30;

 public:
  explicit HealingState(const std::shared_ptr<Role> &role)
      : State(role, "Healing", kRemainingTurns) {}
  void RoundStartEvent() override;
  std::shared_ptr<State> RoundEndEvent() override;
};

class OrderlessState : public State {
  constexpr static int kRemainingTurns = 3;

 public:
  explicit OrderlessState(const std::shared_ptr<Role> &role)
      : State(role, "Orderless", kRemainingTurns) {}
};

class StockpileState : public State {
  constexpr static int kRemainingTurns = 2;

 public:
  explicit StockpileState(const std::shared_ptr<Role> &role)
      : State(role, "Stockpile", kRemainingTurns) {}
  void HandleDamage(int hp) override;
  std::shared_ptr<State> RoundEndEvent() override;
};

class EruptingState : public State {
  constexpr static int kRemainingTurns = 3;

 public:
  explicit EruptingState(const std::shared_ptr<Role> &role)
      : State(role, "Erupting", kRemainingTurns) {}
  std::shared_ptr<State> RoundEndEvent() override;
};

class TeleportState : public State {
  constexpr static int kRemainingTurns = 1;

 public:
  explicit TeleportState(const std::shared_ptr<Role> &role)
      : State(role, "Teleport", kRemainingTurns) {}
};
