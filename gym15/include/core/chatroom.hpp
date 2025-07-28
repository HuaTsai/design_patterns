#pragma once

#include <core/tag.hpp>
#include <memory>
#include <string>
#include <vector>

class WaterballCommunity;
class User;

struct Message {
  std::weak_ptr<User> user;
  std::string content;
  std::vector<Tag> tags;
};

class ChatRoom {
 public:
  explicit ChatRoom(std::shared_ptr<WaterballCommunity> community);
  void SendMessage(const Message &message);

  Message last_message() const { return last_message_; }

 private:
  Message last_message_;
  std::weak_ptr<WaterballCommunity> community_;
};