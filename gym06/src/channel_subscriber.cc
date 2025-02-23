#include "channel_subscriber.hpp"

ChannelSubscriber::ChannelSubscriber(std::string name) : name_(name) {}

std::string ChannelSubscriber::name() const { return name_; }
