#pragma once

#include <core/broadcast.hpp>
#include <core/chatroom.hpp>
#include <core/fourm.hpp>
#include <core/robot.hpp>
#include <core/user.hpp>
#include <memory>

enum class TimeUnit {
  kSeconds,
  kMinutes,
  kHours,
};

class WaterballCommunity : public std::enable_shared_from_this<WaterballCommunity> {
 public:
  WaterballCommunity();

  std::shared_ptr<User> AddUser(std::string id, Permission permission);
  void AddRobot(std::shared_ptr<Robot> robot);
  void Start(int epoch_time, int quota);
  void Wait(int amount, TimeUnit unit);
  void ConsumeQuota(int amount);

  int current_time() const { return current_time_; }
  int quota() const { return quota_; }
  int last_elapsed_time() const { return last_elapsed_time_; }
  std::vector<std::shared_ptr<User>> users() const { return users_; }
  std::shared_ptr<ChatRoom> chat_room() const { return chat_room_; }
  std::shared_ptr<Fourm> fourm() const { return fourm_; }
  std::shared_ptr<Broadcast> broadcast() const { return broadcast_; }
  std::vector<std::shared_ptr<Robot>> robots() const { return robots_; }

 private:
  int quota_;
  int current_time_;
  int last_elapsed_time_;
  std::vector<std::shared_ptr<User>> users_;
  std::shared_ptr<ChatRoom> chat_room_;
  std::shared_ptr<Fourm> fourm_;
  std::shared_ptr<Broadcast> broadcast_;
  std::vector<std::shared_ptr<Robot>> robots_;
};