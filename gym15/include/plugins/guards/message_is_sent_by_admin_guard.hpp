#pragma once

#include <fsm/guard.hpp>

class MessageIsSentByAdminGuard : public Guard {
 public:
  MessageIsSentByAdminGuard() = default;
  bool operator()() const override;
};