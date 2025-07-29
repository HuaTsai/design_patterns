#pragma once

#include <fsm/guard.hpp>
#include <functional>

class QuotaCountGuard : public Guard {
 public:
  explicit QuotaCountGuard(int threshold, const std::function<bool(int, int)> &compare);
  bool operator()() const override;

 private:
  int threshold_;
  std::function<bool(int, int)> compare_;
};