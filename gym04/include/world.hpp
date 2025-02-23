#pragma once

#include <memory>
#include <vector>

#include "collision.hpp"
#include "sprite.hpp"

class World {
  static constexpr int kWorldLength = 30;
  static constexpr int kNumOfInitialSprites = 10;

 public:
  explicit World();
  void Draw() const;
  void Move(int x1, int x2);

 private:
  std::vector<std::shared_ptr<Sprite>> sprites_;
  std::shared_ptr<Collision> collision_;
};
