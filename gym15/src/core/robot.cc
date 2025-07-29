#include <core/chatroom.hpp>
#include <core/robot.hpp>
#include <core/waterball_community.hpp>

Robot::Robot(const std::string &id, std::shared_ptr<WaterballCommunity> community)
    : User(id, Status::kOnline, Permission::kRobot, community) {}

std::shared_ptr<Robot> Robot::CreateRobot(const std::string &id,
                                          std::shared_ptr<WaterballCommunity> community) {
  auto robot = std::make_shared<Robot>(id, community);
  RegisterUser(id, robot);
  return robot;
}

void Robot::Trigger(Event event) { fsm_->Trigger(event); }