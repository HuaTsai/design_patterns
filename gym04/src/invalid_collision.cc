#include "invalid_collision.hpp"

#include <iostream>

#include "sprite.hpp"

bool InvalidCollision::Match(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  auto &s1 = *sprites[x1].get();
  auto &s2 = *sprites[x2].get();

  if (typeid(s1) == typeid(FireSprite) && typeid(s2) == typeid(FireSprite)) {
    return true;
  }

  if (typeid(s1) == typeid(WaterSprite) && typeid(s2) == typeid(WaterSprite)) {
    return true;
  }

  if (typeid(s1) == typeid(HeroSprite) && typeid(s2) == typeid(HeroSprite)) {
    return true;
  }

  return false;
}

void InvalidCollision::CollideImpl(std::vector<std::shared_ptr<Sprite>> & /* sprites */,
                                   int /* x1 */, int /* x2 */) {
  std::cout << "Invalid collision\n";
}
