#pragma once

#include <core/string_hash.hpp>
#include <core/tag.hpp>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class WaterballCommunity;
class User;

class Comment {
 public:
  explicit Comment(std::shared_ptr<User> author, const std::string &content,
                   const std::vector<Tag> &tags);

  std::shared_ptr<User> author() const { return author_.lock(); }
  std::string content() const { return content_; }

 private:
  std::weak_ptr<User> author_;
  std::string content_;
  std::vector<Tag> tags_;
};

class Post {
 public:
  explicit Post(const std::string &id, std::shared_ptr<User> author, const std::string &title,
                const std::string &content, const std::vector<Tag> &tags);
  void AddComment(std::shared_ptr<User> author, const std::string &content,
                  const std::vector<Tag> &tags);

  std::string id() const { return id_; }
  std::shared_ptr<User> author() const { return author_.lock(); }
  std::string title() const { return title_; }
  std::string content() const { return content_; }

 private:
  std::string id_;
  std::weak_ptr<User> author_;
  std::string title_;
  std::string content_;
  std::vector<Tag> tags_;
  std::vector<Comment> comments_;
};

class Fourm {
 public:
  explicit Fourm(std::shared_ptr<WaterballCommunity> community);
  void AddPost(const std::string &id, std::shared_ptr<User> author, const std::string &title,
               const std::string &content, const std::vector<Tag> &tags);

  std::vector<std::shared_ptr<Post>> posts() const { return posts_; }

 private:
  std::weak_ptr<WaterballCommunity> community_;
  std::vector<std::shared_ptr<Post>> posts_;
  std::unordered_set<std::string, StringHash, std::equal_to<>> post_ids_;
};