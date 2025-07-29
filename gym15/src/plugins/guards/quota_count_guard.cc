#include <core/waterball_community.hpp>
#include <plugins/guards/quota_count_guard.hpp>

QuotaCountGuard::QuotaCountGuard(int threshold, const std::function<bool(int, int)> &compare)
    : threshold_(threshold), compare_(compare) {}

bool QuotaCountGuard::operator()() const {
  auto quota = parent_fsm()->robot()->community()->quota();
  return compare_(quota, threshold_);
}
