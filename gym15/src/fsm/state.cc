#include <core/waterball_community.hpp>
#include <fsm/finite_state_machine.hpp>
#include <fsm/state.hpp>

State::State(std::shared_ptr<FiniteStateMachine> child_fsm) : child_fsm_(child_fsm) {}

void State::Enter() { OnEnter(); }

Event State::Do(Event event) {
  auto ret = OnDo(event);
  if (child_fsm_) {
    child_fsm_->Trigger(event);
    if (child_fsm_->is_final_state()) {
      return Event::kStateEnd;
    }
  }
  return ret;
}

void State::Exit() {
  if (child_fsm_) {
    child_fsm_->state()->Exit();
  }
  OnExit();
}