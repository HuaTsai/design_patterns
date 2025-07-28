#pragma once

#include <fsm/guard.hpp>

class MessageContentEqualGuard : public Guard {
 public:
  explicit MessageContentEqualGuard(const std::string &expect_content);
  bool operator()() const override;

 private:
  std::string expect_content_;
};