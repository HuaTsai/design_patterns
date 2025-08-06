#pragma once

#include <direction.hpp>
#include <map_object.hpp>
#include <memory>
#include <state.hpp>

class Role : public MapObject, public std::enable_shared_from_this<Role> {
 public:
  explicit Role(const std::string &symbol, int row, int col, int hp, int power);

  void SetDefaultState();
  void Move(Direction direction);
  void Attack(const std::shared_ptr<Role> &role) const;
  void Damage(int hp);
  void Heal(int hp);
  bool IsFullHealth() const;
  void SetState(const std::shared_ptr<State> &state) { state_ = state; }

  [[nodiscard]] int hp() const { return hp_; }
  [[nodiscard]] int max_hp() const { return max_hp_; }

  [[nodiscard]] std::shared_ptr<State> state() const { return state_; }

 private:
  int hp_;
  int max_hp_;
  int power_;
  std::shared_ptr<State> state_;
};
