#include "world.hpp"

#include <algorithm>
#include <format>
#include <print>
#include <random>

#include "cancel_collision.hpp"
#include "damage_collision.hpp"
#include "heal_collision.hpp"
#include "invalid_collision.hpp"

World::World() : sprites_(kWorldLength) {
  std::default_random_engine gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, 2);
  for (int i = 0; i < kNumOfInitialSprites; ++i) {
    auto rn = dis(gen);
    if (rn == 0) {
      sprites_[i] = std::make_shared<FireSprite>();
    } else if (rn == 1) {
      sprites_[i] = std::make_shared<WaterSprite>();
    } else if (rn == 2) {
      sprites_[i] = std::make_shared<HeroSprite>();
    } else {
      throw std::runtime_error("Invalid random number");
    }
  }
  std::ranges::shuffle(sprites_, gen);

  // clang-format off
  collision_ = std::make_shared<InvalidCollision>(
      std::make_shared<CancelCollision>(
          std::make_shared<HealCollision>(
              std::make_shared<DamageCollision>())));
  // clang-format on
}

void World::Draw() const {
  std::print("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9\n");
  for (const auto &sprite : sprites_) {
    if (sprite) {
      std::print("{} ", sprite->entity());
    } else {
      std::print("_ ");
    }
  }
  std::print("\n");
}

void World::Move(int x1, int x2) {
  if (x1 < 0 || x2 < 0 || x1 >= kWorldLength || x2 >= kWorldLength) {
    std::print("Out of range coordinate(s)\n");
    return;
  }

  if (!sprites_[x1]) {
    std::print("No sprite at location {}\n", x1);
    return;
  }

  if (!sprites_[x2]) {
    std::swap(sprites_[x1], sprites_[x2]);
    return;
  }

  collision_->Collide(sprites_, x1, x2);
}
