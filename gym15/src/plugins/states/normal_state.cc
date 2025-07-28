#include <core/waterball_community.hpp>
#include <plugins/states/default_conversation_state.hpp>
#include <plugins/states/interacting_state.hpp>
#include <plugins/states/normal_state.hpp>

void NormalState::OnEnter() {
  auto users = parent_fsm()->robot()->community()->users();
  int current_online_users = 0;
  for (const auto &user : users) {
    if (user->status() == Status::kOnline) {
      ++current_online_users;
    }
  }

  std::shared_ptr<DefaultConversationState> default_conversation_state;
  std::shared_ptr<InteractingState> interacting_state;

  auto states = child_fsm()->states();
  for (const auto &state : states) {
    if (auto dcs = std::dynamic_pointer_cast<DefaultConversationState>(state)) {
      default_conversation_state = dcs;
    }
    if (auto is = std::dynamic_pointer_cast<InteractingState>(state)) {
      interacting_state = is;
    }
  }

  if (current_online_users < 10) {
    child_fsm()->Initialize(default_conversation_state);
  } else {
    child_fsm()->Initialize(interacting_state);
  }
}

Event NormalState::OnDo(Event event) { return event; }

void NormalState::OnExit() {}