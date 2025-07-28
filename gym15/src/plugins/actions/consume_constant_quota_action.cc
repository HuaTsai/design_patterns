#include <core/waterball_community.hpp>
#include <plugins/actions/consume_constant_quota_action.hpp>

ConsumeConstantQuotaAction::ConsumeConstantQuotaAction(int quota) : quota_(quota) {}

void ConsumeConstantQuotaAction::operator()() const {
  parent_fsm()->robot()->community()->ConsumeQuota(quota_);
}
