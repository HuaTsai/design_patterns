#pragma once

#include <fsm/state.hpp>

class RecordingState : public State {
 public:
  using State::State;

  void OnEnter() override;
  Event OnDo(Event event) override;
  void OnExit() override;

  void set_recorder_id(std::string_view recorder_id) { recorder_id_ = recorder_id; }

 private:
  std::string recording_data_;
  std::string recorder_id_;
};