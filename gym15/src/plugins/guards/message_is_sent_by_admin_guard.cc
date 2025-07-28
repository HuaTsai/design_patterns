#include <core/waterball_community.hpp>
#include <plugins/guards/message_is_sent_by_admin_guard.hpp>

bool MessageIsSentByAdminGuard::operator()() const {
  auto user = parent_fsm()->robot()->community()->chat_room()->last_message().user.lock();
  return user->permission() == Permission::kAdmin;
}