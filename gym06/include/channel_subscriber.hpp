#pragma once

#include <memory>

#include "video.hpp"

class Channel;

class ChannelSubscriber : public std::enable_shared_from_this<ChannelSubscriber> {
 public:
  explicit ChannelSubscriber(std::string name);

  virtual ~ChannelSubscriber() = default;
  ChannelSubscriber(const ChannelSubscriber&) = delete;
  ChannelSubscriber& operator=(const ChannelSubscriber&) = delete;
  ChannelSubscriber(ChannelSubscriber&&) = delete;
  ChannelSubscriber& operator=(ChannelSubscriber&&) = delete;

  virtual void Receive(std::shared_ptr<Channel> channel, std::shared_ptr<Video> video) = 0;
  std::string name() const;

 private:
  std::string name_;
};
