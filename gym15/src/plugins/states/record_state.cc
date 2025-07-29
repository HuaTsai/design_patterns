#include <core/waterball_community.hpp>
#include <plugins/states/record_state.hpp>
#include <plugins/states/recording_state.hpp>
#include <plugins/states/waiting_state.hpp>

void RecordState::OnEnter() {
  auto community = parent_fsm()->robot()->community();
  auto speaker = community->broadcast()->speaker();
  recorder_id_ = community->chat_room()->last_message().user.lock()->id();

  std::shared_ptr<RecordingState> recording_state;
  std::shared_ptr<WaitingState> waiting_state;

  auto states = child_fsm()->states();
  for (const auto &state : states) {
    if (auto rs = std::dynamic_pointer_cast<RecordingState>(state)) {
      recording_state = rs;
    }
    if (auto ws = std::dynamic_pointer_cast<WaitingState>(state)) {
      waiting_state = ws;
    }
  }

  recording_state->set_recorder_id(recorder_id_);
  if (speaker) {
    child_fsm()->Initialize(recording_state);
  } else {
    child_fsm()->Initialize(waiting_state);
  }
}

Event RecordState::OnDo(Event event) { return event; }

void RecordState::OnExit() { /* nop */
}