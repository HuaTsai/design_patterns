#pragma once

#include <fsm/state.hpp>

class NormalState : public State {
 public:
  using State::State;

  void OnEnter() override;
  Event OnDo(Event event) override;
  void OnExit() override;
};