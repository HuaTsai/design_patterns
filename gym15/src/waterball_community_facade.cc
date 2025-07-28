#include <waterball_community_facade.hpp>

namespace {
int ParseTimeString(const std::string &time_str) {
  std::tm tm = {};
  std::istringstream ss(time_str);
  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
  return static_cast<int>(std::mktime(&tm));
}
}  // namespace

WaterballCommunityFacade::WaterballCommunityFacade() : community_(new WaterballCommunity()) {}

std::shared_ptr<Robot> WaterballCommunityFacade::CreateRobot(const std::string &id) {
  auto robot = Robot::CreateRobot(id, community_);
  community_->AddRobot(robot);
  return robot;
}

void WaterballCommunityFacade::AssociateRobotWithFSM(const std::string &id,
                                                     std::shared_ptr<FiniteStateMachine> fsm) {
  auto user = User::GetUser(id);
  if (auto robot = std::dynamic_pointer_cast<Robot>(user)) {
    robot->set_fsm(fsm);
  }
}

void WaterballCommunityFacade::Input(const std::string &action, const nlohmann::json &input) {
  if (action == "started") {
    auto epoch = ParseTimeString(input["time"].get<std::string>());
    auto quota = input["quota"].get<int>();
    community_->Start(epoch, quota);
  } else if (action == "login") {
    auto id = input["userId"].get<std::string>();
    auto permission = input["isAdmin"].get<bool>() ? Permission::kAdmin : Permission::kMember;
    auto user = community_->AddUser(id, permission);
    user->Login();
  } else if (action == "logout") {
    auto user = User::GetUser(input["userId"].get<std::string>());
    user->Logout();
  } else if (action == "new message") {
    auto user = User::GetUser(input["authorId"].get<std::string>());
    auto content = input["content"].get<std::string>();
    auto tags = ParseJsonTags(input["tags"]);
    user->SendMessage(content, tags);
  } else if (action == "new post") {
    auto user = User::GetUser(input["authorId"].get<std::string>());
    auto post_id = input["id"].get<std::string>();
    auto title = input["title"].get<std::string>();
    auto content = input["content"].get<std::string>();
    auto tags = ParseJsonTags(input["tags"]);
    user->NewPost(post_id, title, content, tags);
  } else if (action == "go broadcasting") {
    auto user = User::GetUser(input["speakerId"].get<std::string>());
    user->GoBroadcasting();
  } else if (action == "speak") {
    auto user = User::GetUser(input["speakerId"].get<std::string>());
    auto content = input["content"].get<std::string>();
    user->Speak(content);
  } else if (action == "stop broadcasting") {
    auto user = User::GetUser(input["speakerId"].get<std::string>());
    user->StopBroadcasting();
  } else if (action.ends_with("elapsed")) {
    std::istringstream iss(action);
    int amount = 0;
    std::string unit;
    if (iss >> amount >> unit) {
      if (unit == "second" || unit == "seconds") {
        community_->Wait(amount, TimeUnit::kSeconds);
      } else if (unit == "minute" || unit == "minutes") {
        community_->Wait(amount, TimeUnit::kMinutes);
      } else if (unit == "hour" || unit == "hours") {
        community_->Wait(amount, TimeUnit::kHours);
      }
    }
  }
}
