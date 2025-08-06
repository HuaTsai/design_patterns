#include "channel.hpp"

#include <format>
#include <iostream>

#include "channel_subscriber.hpp"

Channel::Channel(const std::string &name) : name_(name) {}

void Channel::Subscribe(std::shared_ptr<ChannelSubscriber> subscriber) {
  std::cout << std::format("{} 訂閱了 {}。\n", subscriber->name(), name_);
  subscribers_.push_back(subscriber);
}

void Channel::Unsubscribe(std::shared_ptr<ChannelSubscriber> subscriber) {
  std::erase(subscribers_, subscriber);
  std::cout << std::format("{} 解除訂閱了 {}。\n", subscriber->name(), name_);
}

void Channel::Upload(std::shared_ptr<Video> video) {
  std::cout << std::format("頻道 {} 上架了一則新影片 \"{}\"。\n", name_, video->title());
  for (const auto &subscriber : subscribers_) {
    subscriber->Receive(shared_from_this(), video);
  }
}
