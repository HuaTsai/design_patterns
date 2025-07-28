#pragma once

#include <fsm/guard.hpp>

class MessageIsSentByRecorderGuard : public Guard {
 public:
  MessageIsSentByRecorderGuard() = default;
  bool operator()() const override;
};