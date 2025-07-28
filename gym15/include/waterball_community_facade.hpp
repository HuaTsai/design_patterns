#pragma once

#include <core/waterball_community.hpp>
#include <fsm/finite_state_machine.hpp>
#include <nlohmann/json.hpp>

class WaterballCommunityFacade {
 public:
  WaterballCommunityFacade();

  std::shared_ptr<Robot> CreateRobot(const std::string &id);
  static void AssociateRobotWithFSM(const std::string &id, std::shared_ptr<FiniteStateMachine> fsm);
  void Input(const std::string &action, const nlohmann::json &input = nlohmann::json::object());

 private:
  std::shared_ptr<WaterballCommunity> community_;
};