#include <fsm/finite_state_machine.hpp>

FiniteStateMachine::FiniteStateMachine(std::shared_ptr<Robot> robot,
                                       const std::vector<std::shared_ptr<State>> &states,
                                       const std::vector<Transition> &transitions)
    : robot_(robot),
      state_(nullptr),
      states_(states),
      transitions_(transitions),
      is_final_state_(false) {}

void FiniteStateMachine::Initialize(std::shared_ptr<State> initial_state) {
  state_ = initial_state;
  is_final_state_ = false;
  state_->Enter();
}

void FiniteStateMachine::Trigger(Event event) {
  if (is_final_state_) {
    return;
  }
  event = state_->Do(event);
  for (const auto &transition : transitions_) {
    if (transition.from_state() == state_ && transition.event() == event) {
      bool passed = true;
      for (const auto &guard : transition.guards()) {
        if (!(*guard)()) {
          passed = false;
          break;
        }
      }
      if (!passed) {
        continue;
      }
      state_->Exit();
      for (const auto &action : transition.actions()) {
        (*action)();
      }
      state_ = transition.to_state();
      state_->Enter();
      return;
    }
  }
}