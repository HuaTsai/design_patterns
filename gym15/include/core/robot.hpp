#pragma once

#include <core/event.hpp>
#include <core/user.hpp>
#include <fsm/finite_state_machine.hpp>

class WaterballCommunity;

class Robot : public User {
 public:
  static std::shared_ptr<Robot> CreateRobot(const std::string &id,
                                            std::shared_ptr<WaterballCommunity> community);
  void Trigger(Event event);

  void set_fsm(std::shared_ptr<FiniteStateMachine> fsm) { fsm_ = fsm; }
  std::shared_ptr<WaterballCommunity> community() const { return community_.lock(); }

 private:
  Robot(const std::string &id, std::shared_ptr<WaterballCommunity> community);
  std::shared_ptr<FiniteStateMachine> fsm_;
  std::weak_ptr<WaterballCommunity> community_;
};