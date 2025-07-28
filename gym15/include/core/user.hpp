#pragma once

#include <core/tag.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class Status { kOnline, kOffline };

enum class Permission { kAdmin, kMember, kRobot };

class WaterballCommunity;

class User : public std::enable_shared_from_this<User> {
 public:
  virtual ~User() = default;
  User(const User &) = delete;
  User &operator=(const User &) = delete;
  User(User &&) = delete;
  User &operator=(User &&) = delete;

  static std::shared_ptr<User> CreateUser(const std::string &id, Status status,
                                          Permission permission,
                                          std::shared_ptr<WaterballCommunity> community);
  static std::shared_ptr<User> GetUser(const std::string &id);

  void Login();
  void Logout();
  void SendMessage(const std::string &content, const std::vector<Tag> &tags);
  void NewPost(const std::string &id, const std::string &title, const std::string &content,
               const std::vector<Tag> &tags);
  void Comment(const std::string &post_id, const std::string &content,
               const std::vector<Tag> &tags);
  void GoBroadcasting();
  void Speak(const std::string &content);
  void StopBroadcasting();

  std::string id() const { return id_; }
  Status status() const { return status_; }
  Permission permission() const { return permission_; }

 protected:
  explicit User(const std::string &id, Status status, Permission permission,
                std::shared_ptr<WaterballCommunity> community);

  std::string id_;
  Status status_;
  Permission permission_;
  std::weak_ptr<WaterballCommunity> community_;
  static std::unordered_map<std::string, std::shared_ptr<User>> user_map_;
};
