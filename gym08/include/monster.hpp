#pragma once

#include <role.hpp>

class Monster : public Role {
  constexpr static int kMaxHp = 1;
  constexpr static int kPower = 50;

 public:
  explicit Monster(int row, int col);
};
