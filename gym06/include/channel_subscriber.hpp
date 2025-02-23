#pragma once

#include <memory>

#include "video.hpp"

class Channel;

class ChannelSubscriber : public std::enable_shared_from_this<ChannelSubscriber> {
 public:
  ChannelSubscriber(std::string name);
  virtual ~ChannelSubscriber() = default;
  virtual void Receive(std::shared_ptr<Channel> channel, std::shared_ptr<Video> video) = 0;
  std::string name() const;

 protected:
  std::string name_;
};
