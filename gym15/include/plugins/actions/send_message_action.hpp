#pragma once

#include <fsm/action.hpp>

class SendMessageAction : public Action {
 public:
  explicit SendMessageAction(const std::string &message);
  void operator()() const override;

 private:
  std::string message_;
};