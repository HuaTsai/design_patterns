#pragma once

#include <fsm/state.hpp>

class User;

class RecordState : public State {
 public:
  using State::State;

  void OnEnter() override;
  Event OnDo(Event event) override;
  void OnExit() override;

  std::string recorder() const { return recorder_id_; }

 private:
  std::string recorder_id_;
};