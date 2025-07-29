#include <core/waterball_community.hpp>
#include <print>

std::shared_ptr<User> WaterballCommunity::AddUser(const std::string &id, Permission permission) {
  auto user = User::CreateUser(id, Status::kOffline, permission, shared_from_this());
  users_.emplace_back(user);
  return user;
}

void WaterballCommunity::AddRobot(std::shared_ptr<Robot> robot) {
  if (!robot) {
    return;
  }
  robots_.emplace_back(robot);
  users_.emplace_back(robot);
}

void WaterballCommunity::Start(int epoch_time, int quota) {
  current_time_ = epoch_time;
  quota_ = quota;
  chat_room_ = std::make_shared<ChatRoom>(shared_from_this());
  fourm_ = std::make_shared<Fourm>(shared_from_this());
  broadcast_ = std::make_shared<Broadcast>(shared_from_this());
}

void WaterballCommunity::Wait(int amount, TimeUnit unit) {
  using enum TimeUnit;
  if (unit == kSeconds) {
    std::print("🕑 {} seconds elapsed...\n", amount);
    last_elapsed_time_ = amount;
    current_time_ += amount;
  } else if (unit == kMinutes) {
    std::print("🕑 {} minutes elapsed...\n", amount);
    last_elapsed_time_ = amount * 60;
    current_time_ += last_elapsed_time_;
  } else if (unit == kHours) {
    std::print("🕑 {} hours elapsed...\n", amount);
    last_elapsed_time_ = amount * 3600;
    current_time_ += last_elapsed_time_;
  }
  for (const auto &robot : robots_) {
    robot->Trigger(Event::kWait);
  }
}

void WaterballCommunity::ConsumeQuota(int amount) {
  quota_ -= amount;
  if (quota_ < 0) {
    quota_ = 0;
  }
}
