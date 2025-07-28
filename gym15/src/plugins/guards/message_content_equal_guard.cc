#include <core/waterball_community.hpp>
#include <plugins/guards/message_content_equal_guard.hpp>

MessageContentEqualGuard::MessageContentEqualGuard(const std::string &expect_content)
    : expect_content_(expect_content) {}

bool MessageContentEqualGuard::operator()() const {
  auto content = parent_fsm()->robot()->community()->chat_room()->last_message().content;
  return content == expect_content_;
}