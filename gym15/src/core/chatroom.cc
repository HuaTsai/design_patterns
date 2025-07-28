#include <core/chatroom.hpp>
#include <core/event.hpp>
#include <core/user.hpp>
#include <core/waterball_community.hpp>
#include <print>

ChatRoom::ChatRoom(std::shared_ptr<WaterballCommunity> community) : community_(community) {}

void ChatRoom::SendMessage(const Message &message) {
  if (message.user.lock()->permission() != Permission::kRobot) {
    std::print("💬 {}: {} {}\n", message.user.lock()->id(), message.content,
               TagsToString(message.tags));
    last_message_ = message;
    for (const auto &robot : community_.lock()->robots()) {
      robot->Trigger(Event::kSendMessage);
    }
  } else {
    std::print("🤖: {} {}\n", message.content, TagsToString(message.tags));
  }
}
