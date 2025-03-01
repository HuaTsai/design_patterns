#pragma once

#include <memory>

class Role;

class State {
 public:
  explicit State(std::string name, std::shared_ptr<Role> role, int remain_turns);

  virtual ~State() = default;
  State(const State &) = delete;
  State &operator=(const State &) = delete;
  State(State &&) = delete;
  State &operator=(State &&) = delete;

  virtual void Action();
  virtual void Attack(std::shared_ptr<Role> target, int hp);
  virtual void ActionStartEvent();
  void ActionEndEvent();

  [[nodiscard]] std::string name() const;
  [[nodiscard]] std::shared_ptr<Role> role() const;
  [[nodiscard]] std::shared_ptr<State> next_state() const;

 private:
  std::string name_;
  std::weak_ptr<Role> role_;
  int remain_turns_;
  std::shared_ptr<State> next_state_;
};

class NormalState : public State {
 public:
  explicit NormalState(std::shared_ptr<Role> role);
};

class PetrochemicalState : public State {
 public:
  explicit PetrochemicalState(std::shared_ptr<Role> role);
  void Action() override;
};

class PoisonedState : public State {
  static const int kActionStartDamage = 30;

 public:
  explicit PoisonedState(std::shared_ptr<Role> role);
  void ActionStartEvent() override;
};

class CheerupState : public State {
  static const int kBonusDamage = 50;

 public:
  explicit CheerupState(std::shared_ptr<Role> role);
  void Attack(std::shared_ptr<Role> target, int hp) override;
};
