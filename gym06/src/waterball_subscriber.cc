#include "waterball_subscriber.hpp"

void WaterballSubscriber::Receive(std::shared_ptr<Channel> /* channel */,
                                  std::shared_ptr<Video> video) {
  if (video->length() >= 3 * 60) {
    video->Like(name());
  }
}
