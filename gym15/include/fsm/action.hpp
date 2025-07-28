#pragma once

#include <memory>

class FiniteStateMachine;

class Action {
 public:
  Action() = default;
  virtual ~Action() = default;
  Action(const Action &) = delete;
  Action &operator=(const Action &) = delete;
  Action(Action &&) = delete;
  Action &operator=(Action &&) = delete;

  virtual void operator()() const = 0;

  void set_parent_fsm(std::shared_ptr<FiniteStateMachine> parent_fsm) { parent_fsm_ = parent_fsm; }
  std::shared_ptr<FiniteStateMachine> parent_fsm() const { return parent_fsm_.lock(); }

 private:
  std::weak_ptr<FiniteStateMachine> parent_fsm_;
};