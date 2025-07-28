#include <core/waterball_community.hpp>
#include <plugins/guards/message_is_sent_by_recorder_guard.hpp>
#include <plugins/states/record_state.hpp>

bool MessageIsSentByRecorderGuard::operator()() const {
  auto user_id = parent_fsm()->robot()->community()->chat_room()->last_message().user.lock()->id();
  if (auto record_state = dynamic_pointer_cast<RecordState>(parent_fsm()->state())) {
    return record_state->recorder() == user_id;
  }
  return false;
}