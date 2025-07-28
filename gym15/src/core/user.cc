#include <core/user.hpp>
#include <core/waterball_community.hpp>

std::shared_ptr<User> User::CreateUser(const std::string &id, Status status, Permission permission,
                                       std::shared_ptr<WaterballCommunity> community) {
  if (user_map_.contains(id)) {
    throw std::invalid_argument("User already exists.");
  }

  auto user = std::shared_ptr<User>(new User(id, status, permission, community));
  user_map_[id] = user;
  return user;
}

std::shared_ptr<User> User::GetUser(const std::string &id) {
  return user_map_.contains(id) ? user_map_[id] : nullptr;
}

void User::Login() {
  if (status_ == Status::kOnline) {
    return;
  }
  status_ = Status::kOnline;
  for (const auto &robot : community_.lock()->robots()) {
    robot->Trigger(Event::kLogin);
  }
}

void User::Logout() {
  if (status_ == Status::kOffline) {
    return;
  }
  status_ = Status::kOffline;
  for (const auto &robot : community_.lock()->robots()) {
    robot->Trigger(Event::kLogout);
  }
}

void User::SendMessage(const std::string &content, const std::vector<Tag> &tags) {
  if (status_ == Status::kOffline) {
    return;
  }
  auto chat_room = community_.lock()->chat_room();
  const Message message{.user = shared_from_this(), .content = content, .tags = tags};
  chat_room->SendMessage(message);
}

void User::NewPost(const std::string &id, const std::string &title, const std::string &content,
                   const std::vector<Tag> &tags) {
  if (status_ == Status::kOffline) {
    return;
  }
  auto fourm = community_.lock()->fourm();
  fourm->AddPost(id, shared_from_this(), title, content, tags);
}

void User::Comment(const std::string &post_id, const std::string &content,
                   const std::vector<Tag> &tags) {
  auto posts = community_.lock()->fourm()->posts();
  for (const auto &post : posts) {
    if (post->id() == post_id) {
      post->AddComment(shared_from_this(), content, tags);
      return;
    }
  }
}

void User::GoBroadcasting() {
  if (status_ == Status::kOffline) {
    return;
  }
  auto broadcast = community_.lock()->broadcast();
  broadcast->GoBroadcasting(shared_from_this());
}

void User::Speak(const std::string &content) {
  if (status_ == Status::kOffline) {
    return;
  }
  auto broadcast = community_.lock()->broadcast();
  broadcast->Speak(shared_from_this(), content);
}

void User::StopBroadcasting() {
  if (status_ == Status::kOffline) {
    return;
  }
  auto broadcast = community_.lock()->broadcast();
  broadcast->StopBroadcasting(shared_from_this());
}

User::User(const std::string &id, Status status, Permission permission,
           std::shared_ptr<WaterballCommunity> community)
    : id_(id), status_(status), permission_(permission), community_(community) {
  if (id.empty() || id.size() > 20) {
    throw std::invalid_argument("Name must be between 1 and 20 characters.");
  }
}

std::unordered_map<std::string, std::shared_ptr<User>> User::user_map_;
