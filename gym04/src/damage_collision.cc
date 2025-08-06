#include "damage_collision.hpp"

#include <print>

bool DamageCollision::Match(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  auto &s1 = *sprites[x1].get();
  auto &s2 = *sprites[x2].get();

  if (typeid(s1) == typeid(HeroSprite) && typeid(s2) == typeid(FireSprite)) {
    return true;
  }

  if (typeid(s1) == typeid(FireSprite) && typeid(s2) == typeid(HeroSprite)) {
    return true;
  }

  return false;
}

void DamageCollision::CollideImpl(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  auto p1 = dynamic_pointer_cast<HeroSprite>(sprites[x1]);
  auto p2 = dynamic_pointer_cast<HeroSprite>(sprites[x2]);
  std::print("Hero collided with fire and is damaged");
  if (p1) {
    p1->Damage(10);
    if (p1->hp() <= 0) {
      sprites[x1].reset();
      std::print("... died, RIP");
    }
    sprites[x2].reset();
    swap(sprites[x1], sprites[x2]);
  } else {
    p2->Damage(10);
    if (p2->hp() <= 0) {
      sprites[x2].reset();
      std::print("... died, RIP");
    }
    sprites[x1].reset();
  }
  std::print("\n");
}
