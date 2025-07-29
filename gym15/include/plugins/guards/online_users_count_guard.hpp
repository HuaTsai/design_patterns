#pragma once

#include <fsm/guard.hpp>
#include <functional>

class OnlineUsersCountGuard : public Guard {
 public:
  explicit OnlineUsersCountGuard(int threshold, const std::function<bool(int, int)> &compare);
  bool operator()() const override;

 private:
  int threshold_;
  std::function<bool(int, int)> compare_;
};