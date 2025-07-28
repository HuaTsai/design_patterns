#include <core/robot.hpp>
#include <core/tag.hpp>
#include <core/user.hpp>

Tag::Tag(const std::string &id) : id_(id) {}

std::shared_ptr<User> Tag::GetUser() const { return User::GetUser(id_); }

bool Tag::IsRobot() const {
  auto robot = std::dynamic_pointer_cast<Robot>(GetUser());
  return robot != nullptr;
}

std::string TagsToString(const std::vector<Tag> &tags) {
  std::string ret;
  for (const auto &tag : tags) {
    if (!ret.empty()) {
      ret += ", ";
    }
    ret += "@" + tag.id();
  }
  return ret;
}

std::vector<Tag> ParseJsonTags(const nlohmann::json &j) {
  std::vector<Tag> tags;
  for (const auto &tag_str : j.get<std::vector<std::string>>()) {
    tags.emplace_back(tag_str);
  }
  return tags;
}