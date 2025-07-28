#pragma once

#include <memory>
#include <string>

class WaterballCommunity;
class User;

class Broadcast {
 public:
  explicit Broadcast(std::shared_ptr<WaterballCommunity> community);
  void GoBroadcasting(std::shared_ptr<User> user);
  void Speak(std::shared_ptr<User> user, const std::string &content);
  void StopBroadcasting(std::shared_ptr<User> user);

  std::string last_content() const { return last_content_; }
  std::shared_ptr<User> speaker() const { return speaker_.lock(); }

 private:
  std::string last_content_;
  std::weak_ptr<User> speaker_;
  std::weak_ptr<WaterballCommunity> community_;
};