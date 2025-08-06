#include "cancel_collision.hpp"

#include <print>

bool CancelCollision::Match(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  auto &s1 = *sprites[x1].get();
  auto &s2 = *sprites[x2].get();

  if (typeid(s1) == typeid(FireSprite) && typeid(s2) == typeid(WaterSprite)) {
    return true;
  }

  if (typeid(s1) == typeid(WaterSprite) && typeid(s2) == typeid(FireSprite)) {
    return true;
  }

  return false;
}

void CancelCollision::CollideImpl(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  std::print("Water and fire are cancelled\n");
  sprites[x1].reset();
  sprites[x2].reset();
}
