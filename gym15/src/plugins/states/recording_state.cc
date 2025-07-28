#include <core/waterball_community.hpp>
#include <plugins/states/record_state.hpp>
#include <plugins/states/recording_state.hpp>
#include <print>

void RecordingState::OnEnter() { recording_data_.clear(); }

Event RecordingState::OnDo(Event event) {
  if (event == Event::kSpeak) {
    auto content = parent_fsm()->robot()->community()->broadcast()->last_content();
    if (recording_data_.empty()) {
      recording_data_ = "[Record Replay] " + content;
    } else {
      recording_data_ += "\n" + content;
    }
  }
  return event;
}

void RecordingState::OnExit() {
  parent_fsm()->robot()->SendMessage(recording_data_, {Tag(recorder_id_)});
}