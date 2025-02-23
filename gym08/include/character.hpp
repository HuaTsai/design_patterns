#pragma once

#include <role.hpp>

enum class Options : std::uint8_t { kMoveUp, kMoveDown, kMoveLeft, kMoveRight, kAttack, kInvalid };

class Character : public Role {
  constexpr static int kMaxHp = 500;
  constexpr static int kPower = 1;

 public:
  static Options ActionNormal();
  static Options ActionLeftRight();
  static Options ActionUpDown();

  explicit Character(Direction dir, int row, int col);
  Options Action();
  void ShowStatus() const;
  void Turn(Direction dir);

  [[nodiscard]] Direction direction() const { return direction_; }

 private:
  Direction direction_;
};
