#pragma once

#include <memory>
#include <string>
#include <vector>

#include "video.hpp"

class ChannelSubscriber;

class Channel : public std::enable_shared_from_this<Channel> {
 public:
  explicit Channel(std::string name);
  void Subscribe(std::shared_ptr<ChannelSubscriber> subscriber);
  void Unsubscribe(std::shared_ptr<ChannelSubscriber> subscriber);
  void Upload(std::shared_ptr<Video> video);

 private:
  std::string name_;
  std::vector<std::shared_ptr<ChannelSubscriber>> subscribers_;
};
