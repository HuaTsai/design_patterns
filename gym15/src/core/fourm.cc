#include <core/fourm.hpp>
#include <core/user.hpp>
#include <core/waterball_community.hpp>
#include <print>

Comment::Comment(std::shared_ptr<User> author, const std::string &content,
                 const std::vector<Tag> &tags)
    : author_(author), content_(content), tags_(tags) {}

Post::Post(const std::string &id, std::shared_ptr<User> author, const std::string &title,
           const std::string &content, const std::vector<Tag> &tags)
    : id_(id), author_(author), title_(title), content_(content), tags_(tags) {}

void Post::AddComment(std::shared_ptr<User> author, const std::string &content,
                      const std::vector<Tag> &tags) {
  if (author->permission() != Permission::kRobot) {
    std::print("{} comment in post {}: {} {}\n", author->id(), id(), content, TagsToString(tags));
  } else {
    std::print("🤖 comment in post {}: {} {}\n", id(), content, TagsToString(tags));
  }
  comments_.emplace_back(author, content, tags);
}

Fourm::Fourm(std::shared_ptr<WaterballCommunity> community) : community_(community) {}

void Fourm::AddPost(const std::string &id, std::shared_ptr<User> author, const std::string &title,
                    const std::string &content, const std::vector<Tag> &tags) {
  if (post_ids_.contains(id)) {
    return;
  }
  auto post = std::make_shared<Post>(id, author, title, content, tags);
  posts_.emplace_back(post);
  std::print("{}: 【{}】{} {}\n", author->id(), title, content, TagsToString(tags));
  post_ids_.insert(id);
  for (const auto &robot : community_.lock()->robots()) {
    robot->Trigger(Event::kNewPost);
  }
}