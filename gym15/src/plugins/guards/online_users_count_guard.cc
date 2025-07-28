#include <core/waterball_community.hpp>
#include <plugins/guards/online_users_count_guard.hpp>

OnlineUsersCountGuard::OnlineUsersCountGuard(int threshold, std::function<bool(int, int)> compare)
    : threshold_(threshold), compare_(compare) {}

bool OnlineUsersCountGuard::operator()() const {
  auto users = parent_fsm()->robot()->community()->users();
  int current_online_users = 0;
  for (const auto &user : users) {
    if (user->status() == Status::kOnline) {
      ++current_online_users;
    }
  }
  return compare_(current_online_users, threshold_);
}
