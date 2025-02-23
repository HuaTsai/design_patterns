#include "channel.hpp"
#include "fireball_subscriber.hpp"
#include "waterball_subscriber.hpp"

int main() {
  auto waterballch = std::make_shared<Channel>("水球軟體學院");
  auto pewdiepiech = std::make_shared<Channel>("PewDiePie");
  auto waterball = std::make_shared<WaterballSubscriber>("水球");
  auto fireball = std::make_shared<FireballSubscriber>("火球");
  waterballch->Subscribe(waterball);
  pewdiepiech->Subscribe(waterball);
  waterballch->Subscribe(fireball);
  pewdiepiech->Subscribe(fireball);

  auto video1 = std::make_shared<Video>("C1M1S2", "這個世界正是物件導向的呢！", 4 * 60);
  waterballch->Upload(video1);

  auto video2 = std::make_shared<Video>("Hello guys", "Clickbait", 30);
  pewdiepiech->Upload(video2);

  auto video3 = std::make_shared<Video>("C1M1S3", "物件 vs. 類別", 1 * 60);
  waterballch->Upload(video3);

  auto video4 = std::make_shared<Video>("Minecraft", "Let's play Minecraft", 30 * 60);
  pewdiepiech->Upload(video4);
}
