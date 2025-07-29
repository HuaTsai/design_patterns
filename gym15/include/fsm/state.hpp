#pragma once

#include <core/event.hpp>
#include <memory>

class FiniteStateMachine;

class State {
 public:
  State() = default;
  explicit State(std::shared_ptr<FiniteStateMachine> child_fsm);
  virtual ~State() = default;
  State(const State &) = delete;
  State &operator=(const State &) = delete;
  State(State &&) = delete;
  State &operator=(State &&) = delete;

  void Enter();
  virtual void OnEnter() = 0;

  Event Do(Event event);
  virtual Event OnDo(Event event) = 0;

  void Exit();
  virtual void OnExit() = 0;

  void set_parent_fsm(std::shared_ptr<FiniteStateMachine> parent_fsm) { parent_fsm_ = parent_fsm; }
  std::shared_ptr<FiniteStateMachine> parent_fsm() { return parent_fsm_.lock(); }
  std::shared_ptr<FiniteStateMachine> child_fsm() const { return child_fsm_; }

 private:
  std::weak_ptr<FiniteStateMachine> parent_fsm_;
  std::shared_ptr<FiniteStateMachine> child_fsm_;
};
