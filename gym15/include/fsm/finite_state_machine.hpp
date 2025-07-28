#pragma once

#include <core/event.hpp>
#include <fsm/transition.hpp>
#include <vector>

class Robot;

class FiniteStateMachine {
 public:
  explicit FiniteStateMachine(std::shared_ptr<Robot> robot,
                              const std::vector<std::shared_ptr<State>> &states,
                              const std::vector<Transition> &transitions);

  void Initialize(std::shared_ptr<State> initial_state);
  void Trigger(Event event);

  void set_final_state(bool is_final_state) { is_final_state_ = is_final_state; }
  std::shared_ptr<Robot> robot() const { return robot_.lock(); }
  std::shared_ptr<State> state() const { return state_; }
  std::vector<std::shared_ptr<State>> states() const { return states_; }
  std::vector<Transition> transitions() const { return transitions_; }
  bool is_final_state() const { return is_final_state_; }

 private:
  std::weak_ptr<Robot> robot_;
  std::shared_ptr<State> state_;
  std::vector<std::shared_ptr<State>> states_;
  std::vector<Transition> transitions_;
  bool is_final_state_;
};