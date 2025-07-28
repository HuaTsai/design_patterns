#pragma once

#include <memory>

class FiniteStateMachine;

class Guard {
 public:
  Guard() = default;
  virtual ~Guard() = default;
  Guard(const Guard &) = delete;
  Guard &operator=(const Guard &) = delete;
  Guard(Guard &&) = delete;
  Guard &operator=(Guard &&) = delete;

  virtual bool operator()() const = 0;

  void set_parent_fsm(std::shared_ptr<FiniteStateMachine> parent_fsm) { parent_fsm_ = parent_fsm; }
  std::shared_ptr<FiniteStateMachine> parent_fsm() const { return parent_fsm_.lock(); }

 private:
  std::weak_ptr<FiniteStateMachine> parent_fsm_;
};