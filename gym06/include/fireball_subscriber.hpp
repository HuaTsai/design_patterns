#pragma once

#include "channel_subscriber.hpp"

class FireballSubscriber : public ChannelSubscriber {
 public:
  using ChannelSubscriber::ChannelSubscriber;
  void Receive(std::shared_ptr<Channel> channel, std::shared_ptr<Video> video) override;
};
