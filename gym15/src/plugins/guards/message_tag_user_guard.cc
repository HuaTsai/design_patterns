#include <algorithm>
#include <core/waterball_community.hpp>
#include <plugins/guards/message_tag_user_guard.hpp>

MessageTagUserGuard::MessageTagUserGuard(const std::string &expect_user_id)
    : expect_user_id_(expect_user_id) {}

bool MessageTagUserGuard::operator()() const {
  auto tags = parent_fsm()->robot()->community()->chat_room()->last_message().tags;
  return std::ranges::any_of(tags, [this](const auto &tag) { return tag.id() == expect_user_id_; });
}