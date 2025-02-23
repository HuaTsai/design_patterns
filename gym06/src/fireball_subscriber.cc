#include "fireball_subscriber.hpp"

#include "channel.hpp"

void FireballSubscriber::Receive(std::shared_ptr<Channel> channel, std::shared_ptr<Video> video) {
  if (video->length() <= 1 * 60) {
    channel->Unsubscribe(shared_from_this());
  }
}
