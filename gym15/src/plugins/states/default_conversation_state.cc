#include <core/waterball_community.hpp>
#include <plugins/states/default_conversation_state.hpp>

namespace {
const std::array<std::string, 3> repeated_messages = {"good to hear", "thank you", "How are you"};
};

void DefaultConversationState::OnEnter() { cnt_ = 0; }

Event DefaultConversationState::OnDo(Event event) {
  if (event == Event::kSendMessage) {
    auto robot = parent_fsm()->robot();
    auto user_id = robot->community()->chat_room()->last_message().user.lock()->id();
    robot->SendMessage(repeated_messages.at(cnt_), {Tag(user_id)});
    cnt_ = (cnt_ + 1) % static_cast<int>(repeated_messages.size());
  } else if (event == Event::kNewPost) {
    auto robot = parent_fsm()->robot();
    auto last_post = robot->community()->fourm()->posts().back();
    auto postid = last_post->id();
    auto userid = last_post->author()->id();
    robot->Comment(postid, "Nice post", {Tag(userid)});
  }
  return event;
}

void DefaultConversationState::OnExit() {}