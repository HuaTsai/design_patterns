#include <core/waterball_community.hpp>
#include <plugins/states/interacting_state.hpp>

namespace {
const std::array<std::string, 2> repeated_messages = {"Hi hi😁", "I like your idea!"};
};

void InteractingState::OnEnter() { cnt_ = 0; }

Event InteractingState::OnDo(Event event) {
  if (event == Event::kSendMessage) {
    auto robot = parent_fsm()->robot();
    auto user_id = robot->community()->chat_room()->last_message().user.lock()->id();
    robot->SendMessage(repeated_messages.at(cnt_), {Tag(user_id)});
    cnt_ = (cnt_ + 1) % static_cast<int>(repeated_messages.size());
  } else if (event == Event::kNewPost) {
    auto robot = parent_fsm()->robot();
    auto postid = robot->community()->fourm()->posts().back()->id();
    auto users = robot->community()->users();
    std::vector<Tag> tags;
    tags.reserve(users.size());
    for (const auto &user : users) {
      tags.emplace_back(user->id());
    }
    robot->Comment(postid, "How do you guys think about it?", tags);
  }
  return event;
}

void InteractingState::OnExit() { /* nop */ }