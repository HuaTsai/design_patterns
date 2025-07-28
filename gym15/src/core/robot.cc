#include <core/chatroom.hpp>
#include <core/robot.hpp>
#include <core/waterball_community.hpp>

std::shared_ptr<Robot> Robot::CreateRobot(const std::string &id,
                                          std::shared_ptr<WaterballCommunity> community) {
  if (user_map_.contains(id)) {
    throw std::invalid_argument("User already exists.");
  }

  auto robot = std::shared_ptr<Robot>(new Robot(id, community));
  user_map_[id] = robot;
  return robot;
}

void Robot::Trigger(Event event) { fsm_->Trigger(event); }

Robot::Robot(const std::string &id, std::shared_ptr<WaterballCommunity> community)
    : User(id, Status::kOnline, Permission::kRobot, community),
      fsm_(nullptr),
      community_(community) {}