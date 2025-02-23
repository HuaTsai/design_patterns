#pragma once

#include <memory>

#include "collision.hpp"

class HealCollision : public Collision {
 public:
  using Collision::Collision;
  bool Match(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) override;
  void CollideImpl(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) override;
};
