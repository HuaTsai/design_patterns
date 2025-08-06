#include "heal_collision.hpp"

#include <print>

bool HealCollision::Match(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  auto &s1 = *sprites[x1].get();
  auto &s2 = *sprites[x2].get();

  if (typeid(s1) == typeid(HeroSprite) && typeid(s2) == typeid(WaterSprite)) {
    return true;
  }

  if (typeid(s1) == typeid(WaterSprite) && typeid(s2) == typeid(HeroSprite)) {
    return true;
  }

  return false;
}

void HealCollision::CollideImpl(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  std::print("Hero collided with water and is healed\n");
  auto p1 = dynamic_pointer_cast<HeroSprite>(sprites[x1]);
  if (p1) {
    dynamic_pointer_cast<HeroSprite>(sprites[x1])->Heal(10);
    sprites[x2].reset();
    swap(sprites[x1], sprites[x2]);
  } else {
    dynamic_pointer_cast<HeroSprite>(sprites[x2])->Heal(10);
    sprites[x1].reset();
  }
}
