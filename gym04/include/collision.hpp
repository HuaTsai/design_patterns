#pragma once

#include <memory>
#include <vector>

#include "sprite.hpp"

class Collision {
 public:
  explicit Collision(std::shared_ptr<Collision> next = nullptr);
  virtual ~Collision() = default;
  virtual bool Match(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) = 0;
  virtual void CollideImpl(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) = 0;
  void Collide(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2);

 private:
  std::shared_ptr<Collision> next_;
};
