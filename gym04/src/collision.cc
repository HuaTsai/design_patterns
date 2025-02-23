#include "collision.hpp"

Collision::Collision(std::shared_ptr<Collision> next) : next_(next) {}

void Collision::Collide(std::vector<std::shared_ptr<Sprite>> &sprites, int x1, int x2) {
  if (Match(sprites, x1, x2)) {
    CollideImpl(sprites, x1, x2);
  } else if (next_) {
    next_->Collide(sprites, x1, x2);
  }
}
