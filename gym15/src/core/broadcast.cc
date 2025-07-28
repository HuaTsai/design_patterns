#include <core/broadcast.hpp>
#include <core/user.hpp>
#include <core/waterball_community.hpp>
#include <print>

Broadcast::Broadcast(std::shared_ptr<WaterballCommunity> community) : community_(community) {}

void Broadcast::GoBroadcasting(std::shared_ptr<User> user) {
  if (speaker_.lock()) {
    return;
  }
  speaker_ = user;
  if (speaker_.lock()->permission() == Permission::kRobot) {
    std::print("🤖 go broadcasting...\n");
  } else {
    std::print("📢 {} is broadcasting...\n", user->id());
  }
  for (const auto &robot : community_.lock()->robots()) {
    robot->Trigger(Event::kGoBroadcasting);
  }
}

void Broadcast::Speak(std::shared_ptr<User> user, const std::string &content) {
  if (speaker_.lock() != user) {
    return;
  }
  if (speaker_.lock()->permission() == Permission::kRobot) {
    std::print("🤖 speaking: {}\n", content);
  } else {
    std::print("📢 {}: {}\n", user->id(), content);
  }
  last_content_ = content;
  for (const auto &robot : community_.lock()->robots()) {
    robot->Trigger(Event::kSpeak);
  }
}

void Broadcast::StopBroadcasting(std::shared_ptr<User> user) {
  if (speaker_.lock() != user) {
    return;
  }
  if (speaker_.lock()->permission() == Permission::kRobot) {
    std::print("🤖 stop broadcasting...\n");
  } else {
    std::print("📢 {} stop broadcasting\n", user->id());
  }
  speaker_.reset();
  for (const auto &robot : community_.lock()->robots()) {
    robot->Trigger(Event::kStopBroadcasting);
  }
}