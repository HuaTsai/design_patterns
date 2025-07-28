#pragma once

#include <fsm/guard.hpp>

class MessageTagUserGuard : public Guard {
 public:
  explicit MessageTagUserGuard(const std::string &expect_user_id);
  bool operator()() const override;

 private:
  std::string expect_user_id_;
};