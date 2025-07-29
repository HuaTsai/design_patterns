#pragma once

#include <fsm/action.hpp>

class ConsumeConstantQuotaAction : public Action {
 public:
  explicit ConsumeConstantQuotaAction(int quota);
  void operator()() const override;

 private:
  int quota_;
};