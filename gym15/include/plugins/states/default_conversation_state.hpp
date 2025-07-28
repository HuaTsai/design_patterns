#pragma once

#include <fsm/state.hpp>

class DefaultConversationState : public State {
 public:
  using State::State;

  void OnEnter() override;
  Event OnDo(Event event) override;
  void OnExit() override;

 private:
  int cnt_;
};