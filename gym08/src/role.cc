#include <role.hpp>

Role::Role(const std::string &symbol, int row, int col, int hp, int power)
    : MapObject(symbol, row, col), hp_(hp), max_hp_(hp), power_(power) {}

void Role::SetDefaultState() { state_ = std::make_shared<NormalState>(shared_from_this()); }

void Role::Move(Direction direction) {
  switch (direction) {
    case Direction::kUp:
      set_row(row() - 1);
      break;
    case Direction::kDown:
      set_row(row() + 1);
      break;
    case Direction::kLeft:
      set_col(col() - 1);
      break;
    case Direction::kRight:
      set_col(col() + 1);
      break;
    default:
      throw std::runtime_error("Invalid direction");
  }
}

void Role::Attack(const std::shared_ptr<Role> &role) const { role->state_->HandleDamage(power_); }

void Role::Damage(int hp) { hp_ = std::max(0, hp_ - hp); }

void Role::Heal(int hp) { hp_ = std::min(max_hp_, hp_ + hp); }

bool Role::IsFullHealth() const { return hp_ == max_hp_; }
