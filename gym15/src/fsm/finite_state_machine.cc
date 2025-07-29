#include <algorithm>
#include <fsm/finite_state_machine.hpp>

FiniteStateMachine::FiniteStateMachine(std::shared_ptr<Robot> robot,
                                       const std::vector<std::shared_ptr<State>> &states,
                                       const std::vector<Transition> &transitions)
    : robot_(robot), states_(states), transitions_(transitions) {}

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
      if (std::ranges::any_of(transition.guards(), [](const auto &guard) { return !(*guard)(); })) {
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