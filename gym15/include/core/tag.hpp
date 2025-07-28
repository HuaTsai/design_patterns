#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class User;

class Tag {
 public:
  explicit Tag(const std::string &id);
  bool IsRobot() const;
  std::shared_ptr<User> GetUser() const;

  std::string id() const { return id_; }

 private:
  std::string id_;
};

std::string TagsToString(const std::vector<Tag> &tags);

std::vector<Tag> ParseJsonTags(const nlohmann::json &j);
